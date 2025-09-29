import struct

API_OK          = 0
API_ERR         = -1
API_ERR_TIMEOUT = -2

API_CMD_WRITE       = 0x20
API_CMD_GET_STATUS       = 0x21
API_CMD_READ        = 0x22

API_STATUS_BUSY     = 0
API_STATUS_READY    = 1
API_STATUS_ERR      = 2

ARG_READ     = (1<<4)
ARG_WRITE    = (0<<4)
ARG_PTR      = (1<<7)
ARGTYPE_MASK = 0x0F

class baseType:
    def __init__(self, name, ul, idx, fmt, to_fn=None, from_fn=None):
        self.name = name
        self.lenght = ul
        self.idx = idx
        self.fmt = fmt
        self.to_fn = to_fn
        self.from_fn = to_fn

    def to_data(self, value):
        if (self.to_fn != None): value = self.to_fn(value)
        return [ ord(c) if type(c) is str else c for c in struct.pack(self.fmt, value) ]
    
    def from_data(self, data):
        value = struct.unpack(self.fmt, bytes(bytearray(data)))[0]
        if (self.from_fn != None): value = self.from_fn(value)
        return value

BASE_TYPES = {
    'U8': baseType('U8', 1, 0, 'B'),
    'S8': baseType('S8', 1, 1, 'b'),
    'U16': baseType('U16', 2, 2, '<H'),
    'S16': baseType('S16', 2, 3, '<h'),
    'U32': baseType('U32', 4, 4, '<I'),
    'S32': baseType('S32', 4, 5, '<i'),
    'F32': baseType('F32', 4, 6, '<f')
}

def Convert_U8(val):
    assert type(val) == int
    assert val <= 0xFF
    val &= 0xFF
    return 0xFF

def Convert_U16(val):
    if val > 0xFFFF:
        return -1, 0
    val &= 0xFF

def convert_arg_to_bitlist(arg, arg_type):
    # List
    bitlist = []

    for a in arg:
        if arg_type in ['U8', 'PW_U8']:
            byte = a.to_bytes(1, byteorder='big', signed=False)
        elif arg_type in ['S8', 'PW_S8']:
            byte = a.to_bytes(1, byteorder='big', signed=True)
        elif arg_type in ['U16', 'PW_U16']:
            byte = a.to_bytes(2, byteorder='big', signed=False)
        elif arg_type in ['S16', 'PW_S16']:
            byte = a.to_bytes(2, byteorder='big', signed=True)
        elif arg_type in ['U32', 'PW_U32']:
            byte = a.to_bytes(4, byteorder='big', signed=False)
        elif arg_type in ['S32', 'PW_S32']:
            byte = a.to_bytes(4, byteorder='big', signed=True)
        elif arg_type in ['F32', 'PW_F32']:
            byte = a.to_bytes(4, byteorder='big', signed=False)

        bitlist.append(byte)

    return bitlist

"""
retType register_get(addr, *value)

params = {
'id': 1,                        -> Function ID
'args': ['addr','value'],       -> All Arguments (Read+Write)
'nargs': 2,                     -> Len All Arguments
'arg_lens':[4,4]                -> Bytes per Argument
'arg_count':[1, 1]              -> Len of Array of Arg
'cargs': ['u32', 'u32 *']       -> Data Type in C
'arg_types':['U32', 'PR_U32']   -> Arg Type
'wargs':['addr']                -> Write Arg
'rargs':['value']               -> Read Arg

}
"""

def convert_bitlist_to_arg(byte, arg_type):
    print("BYTE",byte)
    val = 0

    if arg_type in ['U8', 'PR_U8']:
        val = int.from_bytes(byte, byteorder='little', signed=False)
    elif arg_type in ['S8', 'PR_S8']:
        val = int.from_bytes(byte, byteorder='little', signed=True)
    elif arg_type in ['U16', 'PR_U16']:
        val = int.from_bytes(byte, byteorder='little', signed=False)
    elif arg_type in ['S16', 'PR_S16']:
        val = int.from_bytes(byte, byteorder='little', signed=True)
    elif arg_type in ['U32', 'PR_U32']:
        val = struct.unpack('<I', byte)[0]
    elif arg_type in ['S32', 'PR_S32']:
        val = int.from_bytes(byte, byteorder='little', signed=True)
    elif arg_type in ['F32', 'PR_F32']:
        val = struct.unpack('<f', byte)[0]  # '<f' = little-endian float32

    return val

def convert_bitlist_to_args(params, data_read):
    args = params['args']
    retVals = []
    print(data_read)

    for i, arg in enumerate(args):
        if arg not in params['rargs']: continue

        arg_type = params['arg_types'][i]
        arg_len  = params['arg_lens'][i]
        arg_count = params['arg_count'][i]
        arg_size = arg_len * arg_count
        
        data = data_read[:arg_size]
        data_len = len(data)

        data_read = data_read[arg_size:]

        argList = []
        for n in range(0, data_len, arg_len):
            bitlist = bytes(data[n:n+arg_len])
            val = convert_bitlist_to_arg(bitlist, arg_type)
            argList.append(val)

        retVals.append(argList)

    return (retVals)

argTypes = {
    "U8"   : { 'val': 0, 'len': 1, 'carg':'u8'},
    "S8"   : { 'val': 1, 'len': 1, 'carg':'s8'},
    "U16"  : { 'val': 2, 'len': 2, 'carg':'u16'},
    "S16"  : { 'val': 3, 'len': 2, 'carg':'s16'},
    "U32"  : { 'val': 4, 'len': 4, 'carg':'u32'},
    "S32"  : { 'val': 5, 'len': 4, 'carg':'s32'},
    "F32"  : { 'val': 6, 'len': 4, 'carg':'f32'},
    "U64"  : { 'val': 7, 'len': 8, 'carg':'u64'},
    "F64"  : { 'val': 8, 'len': 8, 'carg':'f64'},

    "PW_U8"  : { 'val': ARG_PTR | ARG_WRITE | 0, 'len': 1, 'carg':'u8 *'},
    "PW_S8"  : { 'val': ARG_PTR | ARG_WRITE | 1, 'len': 1, 'carg':'s8 *'},
    "PW_U16" : { 'val': ARG_PTR | ARG_WRITE | 2, 'len': 2, 'carg':'u16 *'},
    "PW_S16" : { 'val': ARG_PTR | ARG_WRITE | 3, 'len': 2, 'carg':'s16 *'},
    "PW_U32" : { 'val': ARG_PTR | ARG_WRITE | 4, 'len': 4, 'carg':'u32 *'},
    "PW_S32" : { 'val': ARG_PTR | ARG_WRITE | 5, 'len': 4, 'carg':'s32 *'},
    "PW_F32" : { 'val': ARG_PTR | ARG_WRITE | 6, 'len': 4, 'carg':'f32 *'},
    "PW_U64" : { 'val': ARG_PTR | ARG_WRITE | 7, 'len': 8, 'carg':'u64 *'},
    "PW_F64" : { 'val': ARG_PTR | ARG_WRITE | 8, 'len': 8, 'carg':'f64 *'},

    "PR_U8"  : { 'val': ARG_PTR | ARG_READ | 0, 'len': 1, 'carg':'u8 *'},
    "PR_S8"  : { 'val': ARG_PTR | ARG_READ | 1, 'len': 1, 'carg':'s8 *'},
    "PR_U16" : { 'val': ARG_PTR | ARG_READ | 2, 'len': 2, 'carg':'u16 *'},
    "PR_S16" : { 'val': ARG_PTR | ARG_READ | 3, 'len': 2, 'carg':'s16 *'},
    "PR_U32" : { 'val': ARG_PTR | ARG_READ | 4, 'len': 4, 'carg':'u32 *'},
    "PR_S32" : { 'val': ARG_PTR | ARG_READ | 5, 'len': 4, 'carg':'s32 *'},
    "PR_F32" : { 'val': ARG_PTR | ARG_READ | 6, 'len': 4, 'carg':'f32 *'},
    "PR_U64" : { 'val': ARG_PTR | ARG_READ | 7, 'len': 8, 'carg':'u64 *'},
    "PR_F64" : { 'val': ARG_PTR | ARG_READ | 8, 'len': 8, 'carg':'f64 *'},
}