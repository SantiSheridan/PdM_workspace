ARG_READ     = (1<<4)
ARG_WRITE    = (0<<4)
ARG_PTR      = (1<<7)
ARGTYPE_MASK = 0x0F

def Convert_U8(val):
    assert type(val) == int
    assert val <= 0xFF
    val &= 0xFF
    return 0xFF

def Convert_U16(val):
    if val > 0xFFFF:
        return -1, 0
    val &= 0xFF



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