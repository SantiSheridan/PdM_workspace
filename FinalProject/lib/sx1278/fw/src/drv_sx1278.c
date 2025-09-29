#include "drv_sx1278.h"
#include "api_types.h"
#include "drv_sx1278_port.h"


retType DRV_SX1278_Init(void)
{
    
}
retType DRV_SX1278_SetMode(void);

retType DRV_SX1278_GetVersion(u8 *version)
{
    retType ret = API_OK;

    ret |= DRV_SX1278_Single_RegGet(SX1278_REG_VERSION, version);
    return ret;
}

retType DRV_SX1278_GetRSSI(u8 *rssi){
    retType ret = API_OK;

    ret |= DRV_SX1278_Single_RegGet(SX1278_REG_RSSI_VALUE, rssi);
    return ret;
}