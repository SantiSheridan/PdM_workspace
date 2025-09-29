from api_call import api_call
from api_types import convert_bitlist_to_args


def register_get(addr):
    params = {'id': 0, 'args': ['addr', 'value'], 'nargs': 2, 'wargs': ['addr'], 'rargs': ['value'], 'arg_types': ['U32', 'PR_U32'], 'arg_lens': [4, 4], 'arg_count': [1, 1], 'cargs': ['u32', 'u32 *']}
    ret, data_read = api_call(params, [addr])
    retvals = convert_bitlist_to_args(params, data_read)
    value = retvals[0] 

    return ret, (value) 

def register_set(addr, value):
    params = {'id': 1, 'args': ['addr', 'value'], 'nargs': 2, 'wargs': ['addr', 'value'], 'rargs': [], 'arg_types': ['U32', 'U32'], 'arg_lens': [4, 4], 'arg_count': [1, 1], 'cargs': ['u32', 'u32']}
    ret, data_read = api_call(params, [addr, value])
    retvals = convert_bitlist_to_args(params, data_read)
    

    return ret 

def suma(valu8, valu16):
    params = {'id': 2, 'args': ['valu8', 'valu16', 'resultado'], 'nargs': 3, 'wargs': ['valu8', 'valu16'], 'rargs': ['resultado'], 'arg_types': ['U8', 'U16', 'PR_U32'], 'arg_lens': [1, 2, 4], 'arg_count': [1, 1, 1], 'cargs': ['u8', 'u16', 'u32 *']}
    ret, data_read = api_call(params, [valu8, valu16])
    retvals = convert_bitlist_to_args(params, data_read)
    resultado = retvals[0] 

    return ret, (resultado) 
