#include <stdint.h>
#include <stdlib.h>

#include "buf.h"
#include "crc32.h"

#include "png.h"

void png_encode(uint8_t* bytes, uint32_t wid, uint32_t hei, Buffer buf) {
    buf_write_bytes(buf, "\x89PNG\r\n\x1a\n", 8);

    uint32_t crc;

    crc = ~0;
    buf_write_uint32_be(buf, 13);
    buf_write_bytes(buf, "IHDR", 4);
    buf_write_uint32_be(buf, wid);
    buf_write_uint32_be(buf, hei);
    buf_write_bytes(buf, "\x8\x6\x0\x0\x0", 5);
    buf_write_uint32_be(buf, crc);
}
