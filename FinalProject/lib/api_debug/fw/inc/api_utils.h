#ifndef _API_UTILS_H
#define _API_UTILS_H
#include "api_types.h"

/* RAM VAR */
#define RAM_VAR_SIZE 2048

extern u8 RAM_VAR[RAM_VAR_SIZE];

retType ram_var_set(u32 addr, u32 count, u8* values);
retType ram_var_get(u32 addr, u32 count, u8* values);
retType suma(u8 valu8, u16 valu16, u32 *resultado);

#define RAM_VAR_WRITE_U8(addr, data)     *(u8 *) &RAM_VAR[ ((addr) & 0xFFFF) ] = data
#define RAM_VAR_WRITE_S8(addr, data)     *(s8 *) &RAM_VAR[ ((addr) & 0xFFFF) ] = data
#define RAM_VAR_WRITE_U16(addr, data)    *(u16 *) &RAM_VAR[ ((addr) & 0xFFFF) ] = data
#define RAM_VAR_WRITE_S16(addr, data)    *(s16 *) &RAM_VAR[ ((addr) & 0xFFFF) ] = data
#define RAM_VAR_WRITE_U32(addr, data)    *(u32 *) &RAM_VAR[ ((addr) & 0xFFFF) ] = data
#define RAM_VAR_WRITE_S32(addr, data)    *(s32 *) &RAM_VAR[ ((addr) & 0xFFFF) ] = data
#define RAM_VAR_WRITE_F32(addr, data)    ((f32 *) &RAM_VAR[ ((addr) & 0xFFFF) ])->f = data.f

#define RAM_VAR_READ_U8(addr, pdata)     *(pdata) = *(u8 *) &RAM_VAR[ ((addr) & 0xFFFF) ]
#define RAM_VAR_READ_S8(addr, pdata)     *(pdata) = *(s8 *) &RAM_VAR[ ((addr) & 0xFFFF) ]
#define RAM_VAR_READ_U16(addr, pdata)    *(pdata) = *(u16 *) &RAM_VAR[ ((addr) & 0xFFFF) ]
#define RAM_VAR_READ_S16(addr, pdata)    *(pdata) = *(s16 *) &RAM_VAR[ ((addr) & 0xFFFF) ]
#define RAM_VAR_READ_U32(addr, pdata)    *(pdata) = *(u32 *) &RAM_VAR[ ((addr) & 0xFFFF) ]
#define RAM_VAR_READ_S32(addr, pdata)    *(pdata) = *(s32 *) &RAM_VAR[ ((addr) & 0xFFFF) ]
#define RAM_VAR_READ_F32(addr, pdata)    *(pdata)->f = (*(f32 *) &RAM_VAR[ ((addr) & 0xFFFF) ]).f


/* REGISTERS */
retType register_get(u32 reg, u32 *pval);
retType register_set(u32 reg, u32 val);

#endif // _API_UTILS_H
