
def register_get(addr):
    p = {'id': 1, 'args': ['addr', 'value'], 'nargs': 2, 'wargs': ['addr'], 'rargs': ['value'], 'arg_types': ['U32', 'PR_U32'], 'arg_lens': [4, 4], 'arg_count': [1, 1], 'cargs': ['u32', 'u32 *']}
    api_call(p, [addr])

def register_set(addr, value):
    p = {'id': 0, 'args': ['addr', 'value'], 'nargs': 2, 'wargs': ['addr', 'value'], 'rargs': [], 'arg_types': ['U32', 'U32'], 'arg_lens': [4, 4], 'arg_count': [1, 1], 'cargs': ['u32', 'u32']}
    api_call(p, [addr, value])

def suma(valu8, valu16):
    p = {'id': 2, 'args': ['valu8', 'valu16', 'resultado'], 'nargs': 3, 'wargs': ['valu8', 'valu16'], 'rargs': ['resultado'], 'arg_types': ['U8', 'U16', 'PR_U32'], 'arg_lens': [1, 2, 4], 'arg_count': [1, 1, 1], 'cargs': ['u8', 'u16', 'u32 *']}
    api_call(p, [valu8, valu16])
