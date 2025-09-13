#include <stdint.h>

#ifndef __API_TYPES_H
#define __API_TYPES_H

typedef uint8_t u8;
typedef int8_t s8;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint32_t u32;
typedef int32_t s32;
typedef union {
    uint32_t i;
    float f;
} f32;
typedef double f64;
typedef uint64_t u64;

typedef enum RETTYPE_T {
    API_ERR         = -1,
    API_OK          = 0,
    API_BUSY        = 1,
    API_GO          = 2,
    API_GO_ASYNCH   = 3,
    API_ABORT       = 4
} retType;

#define ARG_READ             (1<<4)
#define ARG_WRITE            (0<<4)
#define ARG_PTR              (1<<7)
#define ARGTYPE_MASK         0x0F
typedef enum ARGTYPE_T {
    U8  = 0,
    S8  = 1,
    U16 = 2,
    S16 = 3,
    U32 = 4,
    S32 = 5,
    F32 = 6,
    U64 = 7,
    F64 = 8,

    PW_U8  = ARG_PTR | ARG_WRITE | U8,
    PW_S8  = ARG_PTR | ARG_WRITE | S8,
    PW_U16 = ARG_PTR | ARG_WRITE | U16,
    PW_S16 = ARG_PTR | ARG_WRITE | S16,
    PW_U32 = ARG_PTR | ARG_WRITE | U32,
    PW_S32 = ARG_PTR | ARG_WRITE | S32,
    PW_F32 = ARG_PTR | ARG_WRITE | F32,
    PW_U64 = ARG_PTR | ARG_WRITE | U64,
    PW_F64 = ARG_PTR | ARG_WRITE | F64,

    PR_U8  = ARG_PTR | ARG_READ | U8,
    PR_S8  = ARG_PTR | ARG_READ | S8,
    PR_U16 = ARG_PTR | ARG_READ | U16,
    PR_S16 = ARG_PTR | ARG_READ | S16,
    PR_U32 = ARG_PTR | ARG_READ | U32,
    PR_S32 = ARG_PTR | ARG_READ | S32,
    PR_F32 = ARG_PTR | ARG_READ | F32,
    PR_U64 = ARG_PTR | ARG_READ | U64,
    PR_F64 = ARG_PTR | ARG_READ | F64,
}ARG_TYPES;

typedef retType (*fptr_0) (void);
typedef retType (*fptr_1) (uintptr_t arg0);
typedef retType (*fptr_2) (uintptr_t arg0, uintptr_t arg1);
typedef retType (*fptr_3) (uintptr_t arg0, uintptr_t arg1, uintptr_t arg2);
typedef retType (*fptr_4) (uintptr_t arg0, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3);
typedef retType (*fptr_5) (uintptr_t arg0, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3, uintptr_t arg4);

retType execute_api(u16 func_id, u8 *data_write, u8 *data_read);

#endif // __API_TYPES_H
