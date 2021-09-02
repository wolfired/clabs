#include <stddef.h>
#include <stdint.h>

#include "buf.h"
#include "flate.h"

void deflate_block(BFINAL is_final, BTYPE type, Buffer compress, Buffer compressed) {
    buf_write_uint8(compressed, (uint8_t)(type | is_final));
    buf_write_uint16_le(compressed, buf_len(compress));
    buf_write_uint16_le(compressed, ~buf_len(compress));
    buf_write_bytes(compressed, buf_take_pointer(compress, 0), buf_len(compress));
}
