import time
import serial
from api_types import *

ser = serial.Serial(
    port='COM6', 
    baudrate=115200, 
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    timeout=1
)

API_CMD_WRITE       = 0x20
API_CMD_GET_STATUS       = 0x21
API_CMD_READ        = 0x22

API_STATUS_BUSY     = 0
API_STATUS_READY    = 1
API_STATUS_ERR      = 2

UART_CMD_START_FRAME = 0x10
UART_CMD_END_FRAME   = 0x11
EXCLUDE_UART_CMD     = 0x7D

receiving = 0
escape_next = 0
frame_buffer = []

"""
UART FRAME FORMAT
+--------------+----------+------------+
| START (0x10) | DataList | END (0x11) |
+--------------+----------+------------+

If DataList contains START or END bytes, add EXCLUDE byte first.
"""
def UART_SendFrame(datalist):
    tx_data = []
    tx_data.append(UART_CMD_START_FRAME)

    for data in datalist:
        if data in [UART_CMD_END_FRAME, UART_CMD_START_FRAME, EXCLUDE_UART_CMD]:
            tx_data.append(EXCLUDE_UART_CMD)
        tx_data.append(data)
    
    tx_data.append(UART_CMD_END_FRAME)
    ser.write(bytes(tx_data))

def UART_ReceiveFrame(timeout=10):
    rx_data = []
    receiving = False
    escape_next = False
    time_s = time.time()

    while True:
        if ((time.time() - time_s) > timeout):
            print("[ERROR]: Timeout al recibir un frame por UART ({} sec)".format(timeout))
            return API_ERR_TIMEOUT, []
        
        if ser.in_waiting:
            byte = ser.read(1)[0]

            if not receiving:
                if byte == UART_CMD_START_FRAME:
                    receiving = True
                    rx_data = []
                    escape_next = False
                    continue
            else:
                if byte == UART_CMD_END_FRAME:
                    return API_OK, rx_data
                
                if escape_next:
                    rx_data.append(byte)
                    escape_next = False
                elif byte == EXCLUDE_UART_CMD:
                    escape_next = True
                else:
                    rx_data.append(byte)

API_CALL_TIMEOUT    = 10 # Sec


"""
API WRITE
                   | -> data receive for execute_api (api_data_write)
+------------------+-------------------+--------------------+
| API CMD (u8) [W] | FUNC ID (u16) [W] | DATA WRITE [W] ... |
+------------------+-------------------+--------------------+

API GET STATUS     | Return By UART Driver (api_status)
+------------------+------------+
| API_CMD (u8) [W] | STATUS (R) | 
+------------------+------------+

API READ           | Return By UART Driver (api_data_read)
+------------------+-------------------+
| API_CMD (u8) [W] | DATA READ [R] ... |
+------------------+-------------------+
"""
def api_call(params, w_args):

    func_id = params['id']
    w_arg_list = []

    # Convertir w_args to individual bytes LSB-MSB
    for i, arg in enumerate(w_args):
        arg_type = params['arg_types'][i] # "U8"
        arg_count = params['arg_count'][i]   # 1 valor en la lista
        assert len(arg) == arg_count, "ERROR: Mas elementos de los que la funcion acepta"
        bitlist = convert_arg_to_bitlist(arg, arg_type)
        for b in bitlist:
            w_arg_list.extend(list(b))

    print(w_arg_list)

    # Write API CALL
    api_write(func_id, w_arg_list)

    # Check API CALL Status
    time.sleep(2)
    ret, status = api_get_status()
    time_s = time.time()
    while(status[0] != API_STATUS_READY):
        time.sleep(2)
        ret, status = api_get_status()
        print(status)
        if status == API_STATUS_ERR: return API_STATUS_ERR, 0

        if (time_s - time.time() > API_CALL_TIMEOUT ): return API_STATUS_ERR, 0

    # Read API CALL
    ret, data_read = api_read()
        
    return ret, data_read


def api_write(func_id, w_args_list):
    func_id_msb = (func_id >> 8) & 0xFF
    fund_id_lsb = func_id & 0xFF
    data_write = [API_CMD_WRITE, func_id_msb, fund_id_lsb]
    for arg in w_args_list:
        data_write.append(arg)
    ret = UART_SendFrame(data_write)
    return ret

def api_get_status():
    data_write = [API_CMD_GET_STATUS]
    ret = UART_SendFrame(data_write)
    ret, status = UART_ReceiveFrame()
    return ret, status

def api_read():
    data_write = [API_CMD_READ]
    ret = UART_SendFrame(data_write)
    ret, data_read = UART_ReceiveFrame()
    return ret, data_read

    

