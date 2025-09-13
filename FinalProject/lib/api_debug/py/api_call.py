import time
import serial

ser = serial.Serial(
    port='COM6', 
    baudrate=115200, 
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    timeout=1
)

CMD_API_WRITE       = 0x20
CMD_API_CHECK       = 0x21
CMD_API_READ        = 0x22

API_STATUS_BUSY     = 0
API_STATUS_READY    = 1
API_STATUS_ERR      = 2

UART_CMD_START_FRAME = 0x10
UART_CMD_END_FRAME   = 0x11
EXCLUDE_UART_CMD     = 0x7D

receiving = 0
escape_next = 0
frame_buffer = []


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
        # if ((time.time() - time_s) > timeout):
        #     print("Timeout: no se recibio frame completo")
        #     return -1
        
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
                    return rx_data
                
                if escape_next:
                    rx_data.append(byte)
                    escape_next = False
                elif byte == EXCLUDE_UART_CMD:
                    escape_next = True
                else:
                    rx_data.append(byte)

API_CALL_TIMEOUT    = 10 # Sec

def api_call(params, w_args):

    func_id = params['id']

    

    # Write API CALL
    api_call_write(func_id, w_args)

    # Check API CALL Status
    time.sleep(2)
    status = api_call_get_status()
    time_s = time.sleep(2)
    while(status != API_STATUS_READY):
        time.sleep(2)
        status = api_call_get_status()
        print(status)
        if status == API_STATUS_ERR: return API_STATUS_ERR, 0

        if (time_s - time.time() > API_CALL_TIMEOUT ): return API_STATUS_ERR, 0

    # Read API CALL
    ret, val = api_call_read()
    
    return ret, val[0:3]


def api_call_write(func_id, w_args_list):
    func_id_msb = (func_id >> 8) & 0xFF
    fund_id_lsb = func_id & 0xFF
    data_write = [CMD_API_WRITE, func_id_msb, fund_id_lsb]
    for arg in w_args_list:
        data_write.append(arg)
    ret = UART_SendFrame(data_write)
    return ret

def api_call_get_status():
    data_write = [CMD_API_CHECK]
    ret = UART_SendFrame(data_write)
    ret, status = UART_ReceiveFrame()
    return ret, status

def api_call_read(r_args_type):
    data_write = [CMD_API_READ]
    ret = UART_SendFrame(data_write)
    ret, r_args_list = UART_ReceiveFrame()
    
    data_read = []
    #convert
    for arg in r_args:
        data_read.append(arg)


    return ret, data_read

    

