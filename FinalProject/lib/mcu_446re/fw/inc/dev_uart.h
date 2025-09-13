#ifndef __DEV_UART_H
#define __DEV_UART_H

#include "stm32f4xx_hal.h"
#include "api_types.h"

extern UART_HandleTypeDef huart4;
extern u8 uart_rx_byte;

retType DEV_UART_Init(void);
retType DEV_UART_SendFrame(u8 *data, u16 length);
retType DEV_UART_ProcessByte(u8 byte);
retType DEV_UART_HandleFrame(u8 *data, u16 length);

#endif //__DEV_UART_H