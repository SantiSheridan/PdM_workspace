#include "api_utils.h"
#include "api_types.h"

/* Array Fijo en RAM */
// u8 *RAM_VAR[RAM_VAR_SIZE] __attribute((section("ramvar")));
u8 RAM_VAR[RAM_VAR_SIZE] = {0};


retType ram_var_set(u32 addr, u32 count, u8* values)
{
    if (addr + count > RAM_VAR_SIZE) return API_ERR;
    
    u8 i;
    for (i=0; i<count; i++)
        RAM_VAR[addr+i] = values[i];

    return API_OK;
}

retType ram_var_get(u32 addr, u32 count, u8* values)
{
    if (addr + count > RAM_VAR_SIZE) return API_ERR;

    u8 i;
    for (i=0; i<count; i++)
        values[i] = RAM_VAR[addr+i]; 
    
    return API_OK;
}

retType register_get(u32 reg, u32 *pval){
    return API_OK;
}
retType register_set(u32 reg, u32 val){
    return API_OK;
}

retType suma(u8 valu8, u16 valu16, u32 *resultado)
{
    *resultado = (u32) valu8 + (u32) valu16;
    return API_OK;
}
