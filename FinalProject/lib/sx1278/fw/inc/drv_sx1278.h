#ifndef __DRV_SX1278_H
#define __DRV_SX1278_H
#include <api_types.h>


/* Registers Address */
#define SX1278_REG_FIFO         0x00
#define SX1278_REG_OP_MODE      0x01
#define SX1278_REG_RSSI_VALUE   0x11
#define SX1278_REG_VERSION      0x42

#define SX1278_REG_MASK     0x7F
#define SX1278_REG_READ     0<<7
#define SX1278_REG_WRITE    1<<7

retType DRV_SX1278_Init(void);
retType DRV_SX1278_SetMode(void);
retType DRV_SX1278_GetVersion(u8 *version);
retType DRV_SX1278_GetRSSI(u8 *rssi);
#endif //__SX1278_H