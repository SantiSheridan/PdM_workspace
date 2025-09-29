#include <string.h>
#include "drv_uart.h"
#include "api_types.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_uart.h"


#define UART_CMD_START_FRAME        0x10
#define UART_CMD_END_FRAME          0x11
#define EXCLUDE_UART_CMD            0x7D


static UART_HandleTypeDef huart4;
static u8 uart_rx_byte;
static u8 frame_buffer[API_BUFFER_SIZE];
static u16 frame_index = 0;
static u8 receiving_frame = 0;
static u8 escape_next = 0;

extern u8 api_data_write[API_BUFFER_SIZE];
extern u8 api_data_read[API_BUFFER_SIZE];
extern u8 api_status;
/*
UART FRAME FORMAT
+--------------+----------------+------------+
| START (0x10) | API_CALL_FRAME | END (0x11) |
+--------------+----------------+------------+

IF API_CALL_FRAME contains START or END bytes, use EXCLUDE command.
*/


retType DRV_UART_Init(void)
{
    huart4.Instance = UART4;
    huart4.Init.BaudRate = 115200;
    huart4.Init.WordLength = UART_WORDLENGTH_8B;
    huart4.Init.StopBits = UART_STOPBITS_1;
    huart4.Init.Parity = UART_PARITY_NONE;
    huart4.Init.Mode = UART_MODE_TX_RX;
    huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart4.Init.OverSampling = UART_OVERSAMPLING_16;
    // if (HAL_UART_Init(&huart4) != HAL_OK)

    HAL_UART_Init(&huart4);
    HAL_UART_MspInit(&huart4);

    HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UART4_IRQn);

    HAL_UART_Receive_IT(&huart4, &uart_rx_byte, 1);
    return API_OK;

}

void UART4_IRQHandler(void) {
    HAL_UART_IRQHandler(&huart4);
}

retType DRV_UART_SendFrame(u8 *data, u16 lenght)
{
    u8 byte;
    u16 tx_index = 0;
    /* Start UART Frame */
    frame_buffer[tx_index++] = UART_CMD_START_FRAME;
    
    // HAL_UART_Transmit(&huart4, &cmd, 1, 10);

    /* API CALL */
    for (u16 i = 0; i < lenght; i++)
    {
        byte = data[i];
        if (byte == UART_CMD_START_FRAME ||
            byte == UART_CMD_END_FRAME   ||
            byte == EXCLUDE_UART_CMD)
        {
            frame_buffer[tx_index++] = EXCLUDE_UART_CMD;
            frame_buffer[tx_index++] = byte;
        }
        else{
            frame_buffer[tx_index++] = byte;
        }
    }

    /* END UART Frame */
    frame_buffer[tx_index++] = UART_CMD_END_FRAME;
    HAL_UART_Transmit_IT(&huart4, frame_buffer, tx_index++);

    return API_OK;
}

retType DRV_UART_ProcessByte(u8 byte)
{
    if (byte == UART_CMD_START_FRAME) {
        receiving_frame = 1;
        frame_index = 0;
        escape_next = 0;
        return API_OK;
    }

    if (byte == UART_CMD_END_FRAME && receiving_frame) {
        receiving_frame = 0;
        DRV_UART_HandleFrame(frame_buffer, frame_index);
        return API_OK;
    }

    if (!receiving_frame) return API_OK;

    if (escape_next) {
        if (frame_index < API_BUFFER_SIZE) {
            frame_buffer[frame_index++] = byte;
        }
        escape_next = 0;
    }
    else if (byte == EXCLUDE_UART_CMD){
        escape_next = 1;
    }
    else {
        if (frame_index < API_BUFFER_SIZE) {
            frame_buffer[frame_index++] = byte;
        }
    }
    return API_OK;
}

retType DRV_UART_HandleFrame(u8 *data, u16 lenght)
{
    u16 func_id=0;
    u8 msb,lsb;
    u8 cmd = data[API_REG_CMD];
    if (lenght > 0) {
        switch (cmd) {
            case API_CMD_WRITE: // API_WRITE
                /* Get Func ID */
                msb = data[API_REG_FUNC_ID_MSB] & 0xFF;
                lsb = data[API_REG_FUNC_ID_LSB] & 0xFF;
                func_id = (msb << 8) | lsb;

                /* Clear buffers*/
                memset(api_data_write, 0, sizeof(api_data_write));
                memset(api_data_read, 0, sizeof(api_data_read));

                /* Write uart data to data buffer */
                memcpy(api_data_write, &data[API_REG_START_WDATA], lenght-API_REG_START_WDATA);
                execute_api(func_id, api_data_write, api_data_read);
                break;
            case API_CMD_GET_STATUS: // API_STATUS
                DRV_UART_SendFrame(&api_status, 1);
                break;
            case API_CMD_READ:
                /* Send all api_data_read buffer */
                DRV_UART_SendFrame(api_data_read, sizeof(api_data_read));
                break;
        }
    }
    return API_OK;
}

/* HAL Callbacks */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == UART4) {
        DRV_UART_ProcessByte(uart_rx_byte);
        HAL_UART_Receive_IT(&huart4, &uart_rx_byte, 1);
    }
}