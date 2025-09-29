#ifndef __DRV_SPI_H
#define __DRV_SPI_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include "api_types.h"

retType DRV_SPI_Init(void);
retType DRV_SPI_TransmitReceive(u8 *ptxData, u8 *prxData, u16 size);
retType DRV_SPI_Transmit(u8 *ptxData, u16 size);
retType DRV_SPI_Receive(u8 *prxData, u16 size);


#endif //__DRV_SPI_H