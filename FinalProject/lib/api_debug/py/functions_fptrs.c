#include "api_types.h"
#include "api_functions.h"


#include "api_utils.h"


const FPTRS FUNCTIONS_FPTRS[FUNCTIONS_COUNT] = {

    // Func id = 0
    {
        .nargs      = 2,
        .arg_types  = { U32, U32 },
        .arg_lens   = { 4, 4 },
        .fptr       = { .f2 = (fptr_2) register_set },
    },

    // Func id = 1
    {
        .nargs      = 2,
        .arg_types  = { U32, PR_U32 },
        .arg_lens   = { 4, 4 },
        .fptr       = { .f2 = (fptr_2) register_get },
    },

    // Func id = 2
    {
        .nargs      = 3,
        .arg_types  = { U8, U16, PR_U32 },
        .arg_lens   = { 1, 2, 4 },
        .fptr       = { .f3 = (fptr_3) suma },
    },

};