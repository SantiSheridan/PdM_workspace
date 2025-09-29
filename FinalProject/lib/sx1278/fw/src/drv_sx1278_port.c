#include "api_types.h"
#include "drv_sx1278_port.h"
#include "drv_sx1278.h"
#include "drv_spi.h"

/*
SX1278 -> SPI Interface - CPOL = 0, CPHA = 0 (Mode 0)
- Full Duplex
- Data is sampled on rising edge of SCK
- MOSI driven by master on falling edge
- MISO driven by slave on falling edge
- CS low = active frame, CS high = idle

Single Access -> wnr bit (1 write, 0 read)
+----------------+------------+
| wnr + reg_addr | DATA_WRITE | -> MOSI
+----------------+------------+
+----------------+-----------+
|        X       | DATA_READ | -> MISO
+----------------+-----------+

Burst Access 
+----------------+-----------------------+---------------------------+
| wnr + reg_addr | DATA_WRITE (reg_addr) | DATA_WRITE (reg_addr + 1) | ... -> MOSI
+----------------+-----------------------+---------------------------+
+----------------+----------------------+--------------------------+
|        X       | DATA_READ (reg_addr) | DATA_READ (reg_addr + 1) | ... -> MISO
+----------------+----------------------+--------------------------+


*/
retType DRV_SX1278_Single_RegSet(u8 addr, u8 val)
{
    retType ret = API_OK;
    u8 txData[2] = {0};
    txData[0] = SX1278_REG_WRITE | (addr & SX1278_REG_MASK);
    txData[1] = val;
    
    ret |= DRV_SPI_Transmit(txData,  2);
    return ret;
}

retType DRV_SX1278_Single_RegGet(u8 addr, u8 *val)
{
    retType ret = API_OK;
    u8 reg_addr = SX1278_REG_READ | (addr & SX1278_REG_MASK);

    ret |= DRV_SPI_TransmitReceive(&reg_addr, val, 2);
    return ret;
}

// retType DRV_SX1278_Burst_RegSet(u8 addr, u8 *values, u8 len)
// {

// }
// retType DRV_SX1278_Burst_RegGet(u8 addr, u8 *values, u8 len)
// {
    
// }

// retType DRV_SX1278_FIFO_RegSet(u8 addr, u8 *values, u8 len);
// retType DRV_SX1278_FIFO_RegGet(u8 addr, u8 *values, u8 len);