/*
 * api_uart.c
 *
 *  Created on: Sep 25, 2025
 *      Author: W10-PC
 */

#include "api_uart.h"
#include <stdbool.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_uart.h"

#define UART_TIMEOUT 100

UART_HandleTypeDef huart4;

bool uartInit()
{
	bool ret = true;

	huart4.Instance = UART4;
	huart4.Init.BaudRate = 115200;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&huart4) != HAL_OK) ret = false;
	HAL_UART_MspInit(&huart4);

	uint8_t configMsg[] =
		"UART 4 Configurada:\r\n"
		"- BaudRate: 115200\r\n"
		"- Word Length: 8 bits\r\n"
		"- Stop Bits: 1\r\n"
		"- Parity: None\r\n"
		"- Mode: Full Duplex\r\n"
		"- Flow Control: None\r\n"
		"- Oversampling: x16\r\n";
	uartSendString(configMsg);

	return ret;
}

void uartSendString(uint8_t* pstring)
{
	if (pstring == NULL) return;
	HAL_UART_Transmit(&huart4, pstring, strlen((char *)pstring), UART_TIMEOUT);
}

void uartSendStringSize(uint8_t* pstring, uint16_t size)
{
	if (pstring == NULL || size == 0) return;
	HAL_UART_Transmit(&huart4, pstring, size, UART_TIMEOUT);
}

void uartReceiveStringSize(uint8_t* pstring, uint16_t size)
{
	if (pstring == NULL || size == 0) return;
	HAL_UART_Receive(&huart4, pstring, size, UART_TIMEOUT);
}
