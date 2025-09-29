#ifndef __DRV_UART_H
#define __DRV_UART_H

#include "stm32f4xx_hal.h"
#include "api_types.h"

retType DRV_UART_Init(void);
retType DRV_UART_SendFrame(u8 *data, u16 length);
retType DRV_UART_ProcessByte(u8 byte);
retType DRV_UART_HandleFrame(u8 *data, u16 length);

#endif //__DRV_UART_H