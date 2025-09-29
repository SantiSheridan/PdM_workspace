#include "api_types.h"
#include "drv_spi.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_spi.h"

SPI_HandleTypeDef hspi1;

retType DRV_SPI_Init(void)
{
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_HARD_OUTPUT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;
    HAL_SPI_Init(&hspi1);
    
    return API_OK;
}

retType DRV_SPI_TransmitReceive(u8 *ptxData, u8 *prxData, u16 size)
{
    HAL_SPI_TransmitReceive(&hspi1, ptxData, prxData, size, HAL_MAX_DELAY);
    return API_OK;
}

retType DRV_SPI_Transmit(u8 *ptxData, u16 size)
{
    HAL_SPI_Transmit(&hspi1, ptxData, size, HAL_MAX_DELAY);
    return API_OK;
}

retType DRV_SPI_Receive(u8 *prxData, u16 size)
{
    HAL_SPI_Receive(&hspi1, prxData, size, HAL_MAX_DELAY);
    return API_OK;
}