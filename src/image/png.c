#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "adler32.h"
#include "buf.h"
#include "crc32.h"

#include "png.h"

void png_magic_header(Buffer buf) {
    buf_write_bytes(buf, (uint8_t[]){137, 80, 78, 71, 13, 10, 26, 10}, 8);
}

void png_write_IHDR(Buffer buf, uint32_t wid, uint32_t hei) {
    buf_write_uint32_be(buf, 13);
    ptrdiff_t crc_begin = buf_mark_pointer_w(buf);
    buf_write_bytes(buf, "IHDR", 4);
    buf_write_uint32_be(buf, wid);
    buf_write_uint32_be(buf, hei);
    buf_write_bytes(buf, "\x8\x6\x0\x0\x0", 5);
    ptrdiff_t crc_end = buf_mark_pointer_w(buf);
    buf_write_uint32_be(buf, crc32(buf_take_pointer(buf, crc_begin), crc_end - crc_begin));
}

void png_write_IEND(Buffer buf) {
    buf_write_bytes(buf, "\x0\x0\x0\x0IEND\xae\x42\x60\x82", 12);
}

void png_encode(uint8_t* bytes, uint32_t wid, uint32_t hei, Buffer buf) {
    ptrdiff_t crc_begin = -1;
    ptrdiff_t crc_end   = -1;

    png_magic_header(buf);
    png_write_IHDR(buf, wid, hei);

    uint32_t  adler32     = 1;
    ptrdiff_t adler_begin = -1;
    ptrdiff_t adler_end   = -1;

    uint16_t line_wid = 1 + wid * 4;
    buf_write_uint32_be(buf, 2 + hei * (5 + line_wid) + 4);
    crc_begin = buf_mark_pointer_w(buf);
    buf_write_bytes(buf, "IDAT", 4);
    buf_write_bytes(buf, "\x78\x1", 2);
    for(size_t y = 0; y < hei; ++y) {
        buf_write_uint8(buf, y == hei - 1);
        buf_write_uint16_le(buf, line_wid);
        buf_write_uint16_le(buf, ~line_wid);

        adler_begin = buf_mark_pointer_w(buf);
        buf_write_uint8(buf, 0);
        buf_write_bytes(buf, bytes, line_wid - 1);
        adler_end = buf_mark_pointer_w(buf);
        adler32_update_bytes(&adler32, buf_take_pointer(buf, adler_begin), adler_end - adler_begin);
    }
    buf_write_uint32_be(buf, adler32);
    crc_end = buf_mark_pointer_w(buf);
    buf_write_uint32_be(buf, crc32(buf_take_pointer(buf, crc_begin), crc_end - crc_begin));

    png_write_IEND(buf);
}
