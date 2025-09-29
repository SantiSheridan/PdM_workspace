#ifndef __DRV_SX1278_PORT_H
#define __DRV_SX1278_PORT_H
#include "api_types.h"
#include "drv_sx1278.h"

retType DRV_SX1278_Single_RegSet(u8 addr, u8 val);
retType DRV_SX1278_Single_RegGet(u8 addr, u8 *val);

retType DRV_SX1278_Burst_RegSet(u8 addr, u8 *values, u8 len);
retType DRV_SX1278_Burst_RegGet(u8 addr, u8 *values, u8 len);

retType DRV_SX1278_FIFO_RegSet(u8 addr, u8 *values, u8 len);
retType DRV_SX1278_FIFO_RegGet(u8 addr, u8 *values, u8 len);

#endif //__DRV_SX1278_PORT_H