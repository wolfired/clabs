#include <stddef.h>
#include <stdint.h>

#include "bufio/buf.h"
#include "compress/flate.h"

void deflate_write_block(BFINAL is_final, BTYPE type, Buffer buffer_uncompress, Buffer buffer_compressed) {
    buf_write_uint8(buffer_compressed, (uint8_t)(type | is_final));
    buf_write_uint16_le(buffer_compressed, buf_len(buffer_uncompress));
    buf_write_uint16_le(buffer_compressed, ~buf_len(buffer_uncompress));
    buf_write_bytes(buffer_compressed, buf_take_pointer(buffer_uncompress, 0), buf_len(buffer_uncompress));
}
