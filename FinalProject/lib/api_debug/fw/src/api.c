#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "api_types.h"
#include "api_functions.h"

/* Registers in the frames*/
/* API CALL COMMANDS */
#define CMD_API_WRITE               0x20
#define CMD_API_CHECK               0x21
#define CMD_API_READ                0x22


/* API CALL STATUS */
#define API_CALL_STATUS_BUSY        0  // The MCU is calling busy with the API CALL                  
#define API_CALL_STATUS_READY       1  // API CALL is ready to read
#define API_CALL_STATUS_ERR         2  // API CALL FAIL


/* Registers in API CALL Frame */
#define REG_API_CMD                 0

/* API_CALL WRITE*/ 
#define REG_API_FUNC_ID_MSB         1
#define REG_API_FUNC_ID_LSB         2
#define REG_API_ARG_TYPES           3
#define REG_API_DATA_WRITE          4

/* API CALL STATUS */
#define REG_API_STATUS              1

/* API CALL READ */
#define REG_API_DATA_READ           1



/*
API CALL FRAME
                   | -> data receive for execute_api
+------------------+-------------------+---------------------+--------------------+
| API CMD (u8) [W] | FUNC ID (u16) [W] | ARG TYPES(8*u8) [W] | DATA WRITE [W] ... |
+------------------+-------------------+---------------------+--------------------+

API CALL FRAME    | Return By UART Driver
+-----------------+------------+
| API_CMD (u8)[W] | STATUS (R) | 
+-----------------+------------+

API_READ          | Return By UART Driver
+-----------------+-------------------+
| API_CMD (u8)[W] | DATA READ [R] ... |
+-----------------+-------------------+
*/



u8 api_data_write[2048] = {0};
u8 api_data_read[2048] = {0};
u8 api_status = 0;
/* 
** data_write = {          Data write          } Filled by UART
**                 0x07 - 0x0000008 - 0x0000
**                  u8       u32       u16
** data_read  = {           Data read          } Filled by exetute_api
**                 0x07 - 0x0000008 - 0x0000
**                  u8       u32       u16
*/

const FPTRS *find_api(u16 func_id)
{
    /* Check if func is valid */
    if (func_id >= FUNCTIONS_COUNT) return NULL;

    return &FUNCTIONS_FPTRS[func_id];
}

retType execute_api(u16 func_id, u8 *data_write, u8 *data_read){
    retType ret = API_OK;
    u32 temp_u32;
    u16 temp_u16, arg_offset_read, arg_offset_write;
    u8 temp_u8, arg_idx;
    uintptr_t args[8] = { 0 };

    /* Processing API */
    api_status = API_CALL_STATUS_BUSY;

    const FPTRS *api = find_api(func_id);

    if (api != NULL)
    {   
        /* Take Api info */
        arg_offset_read  = 0;
        arg_offset_write = 0;


        for (arg_idx = 0; arg_idx < api->nargs; arg_idx++)
        {
            /* The argument is written to data_read */
            if (api->arg_types[arg_idx] & ARG_READ)
            {
                args[arg_idx] = (uintptr_t) &data_read[arg_offset_read];
                arg_offset_read += api->arg_lens[arg_idx];
            }
            /* The argument is taked from data_write*/
            else{
                /* The arg is a pointer */
                if (api->arg_types[arg_idx] & ARG_PTR)
                {
                    u32 *parg = (u32 *) &data_write[arg_offset_write];
                    args[arg_idx] = (uintptr_t) parg;
                }
                /* The arg is a value*/
                else
                {
                    switch (api->arg_types[arg_idx] & ARGTYPE_MASK)
                    {
                    case U8:
                    case S8:{
                        temp_u8 = data_write[arg_offset_write];
                        args[arg_idx] = (uintptr_t) (u8) temp_u8;
                        break;
                    }
                    case U16:
                    case S16:{
                            temp_u16 = (data_write[arg_offset_write] << 8) | data_write[arg_offset_write+1];
                        args[arg_idx] = (uintptr_t) (u16) temp_u16;
                        break;
                    }
                    case U32:
                    case S32:
                    case F32: {
                        temp_u32 = (data_write[arg_offset_write] << 24) | (data_write[arg_offset_write+1] << 16) | (data_write[arg_offset_write+2] << 8) | data_write[arg_offset_write+3];
                        args[arg_idx] = (uintptr_t) (u32) temp_u32;
                        break;
                    }
                    default:
                        api_status = API_CALL_STATUS_ERR;
                        return API_ERR;
                        break;
                    }
                }
                arg_offset_write += api->arg_lens[arg_idx];
            }
        }
        /* API Function Call */
        switch (api->nargs)
        {
            case 0:
                ret = api->fptr.f0();
                break;
            case 1:
                ret = api->fptr.f1(args[0]);
                break;
            case 2:
                ret = api->fptr.f2(args[0], args[1]);
                break;
            case 3:
                ret = api->fptr.f3(args[0], args[1], args[2]);
                break;
            case 4:
                ret = api->fptr.f4(args[0], args[1], args[2], args[3]);
                break;
            case 5:
                ret = api->fptr.f5(args[0], args[1], args[2], args[3], args[4]);
                break;
            default:
                break;
        }
    } else{
        api_status = API_CALL_STATUS_ERR;
        return API_ERR;
    }
    api_status = API_CALL_STATUS_READY;
    return ret;
}

retType test_execute_api(void)
{
    retType ret;
    api_data_write[0] = 10;
    api_data_write[1] = 0; //LSB
    api_data_write[2] = 3; //MSB
    u16 func_index = 2;
    ret = execute_api(func_index, api_data_write, api_data_read);

    return ret;
}
