#ifndef __API_FUNCTIONS_H
#define __API_FUNCTIONS_H

#include "api_types.h"

#define FUNCTIONS_COUNT 4
#define MAX_ARGS 8

typedef struct FPTRS_T {
    u8 nargs;
    u8 arg_types[MAX_ARGS];
    u8 arg_lens[MAX_ARGS];
    union {
        fptr_0 f0;
        fptr_1 f1;
        fptr_2 f2;
        fptr_3 f3;
        fptr_4 f4;
        fptr_5 f5;
    } fptr;
} FPTRS;

extern const FPTRS FUNCTIONS_FPTRS[FUNCTIONS_COUNT];

#endif //__API_FUNCTIONS_H
