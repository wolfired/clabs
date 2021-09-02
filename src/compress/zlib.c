#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bufio/buf.h"
#include "compress/zlib.h"
#include "hash/adler32.h"

void zlib_buf_create(Buffer* p_buffer, ZLibCINFO cinfo, ZLibCM cm, ZLibFLEVEL flevel, ZLibFDICT fdict, uint32_t dictid) {
    buf_create(p_buffer, 0);

    uint16_t cmf_flg = (cinfo | cm) << 8 | (flevel | fdict);
    cmf_flg |= 31 - cmf_flg % 31;
    buf_write_uint16_be(*p_buffer, cmf_flg);
    if(zlib_dict_yes == fdict) { buf_write_uint32_be(*p_buffer, dictid); }
}

void zlib_buf_delete(Buffer* p_buffer) {
    // do other zip's delete

    buf_delete(p_buffer);
}

void zlib_buf_write_compressed_data(Buffer buffer_zlib, Buffer buffer_compressed) {}
