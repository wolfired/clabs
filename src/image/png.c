#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "hash/adler32.h"
#include "bufio/buf.h"
#include "hash/crc32.h"
#include "compress/flate.h"
#include "compress/zlib.h"

#include "image/png.h"

void png_magic_header(Buffer png_buffer) {
    buf_write_bytes(png_buffer, (uint8_t[]){137, 80, 78, 71, 13, 10, 26, 10}, 8);
}

void png_write_IHDR(Buffer png_buffer, uint32_t wid, uint32_t hei) {
    buf_write_uint32_be(png_buffer, 13);
    ptrdiff_t crc_begin = buf_mark_pointer_w(png_buffer);
    buf_write_bytes(png_buffer, "IHDR", 4);
    buf_write_uint32_be(png_buffer, wid);
    buf_write_uint32_be(png_buffer, hei);
    buf_write_bytes(png_buffer, "\x8\x6\x0\x0\x0", 5);
    ptrdiff_t crc_end = buf_mark_pointer_w(png_buffer);
    buf_write_uint32_be(png_buffer, crc32(buf_take_pointer(png_buffer, crc_begin), crc_end - crc_begin));
}

void png_write_IEND(Buffer png_buffer) {
    buf_write_bytes(png_buffer, "\x0\x0\x0\x0IEND\xae\x42\x60\x82", 12);
}

void png_encode(Buffer png_buffer, uint32_t wid, uint32_t hei, uint8_t* pixel_bytes) {
    // ptrdiff_t crc_begin = -1;
    // ptrdiff_t crc_end   = -1;

    png_magic_header(png_buffer);
    png_write_IHDR(png_buffer, wid, hei);

    // uint32_t  adler32     = 1;
    // ptrdiff_t adler_begin = -1;
    // ptrdiff_t adler_end   = -1;

    // uint16_t line_wid = 1 + wid * 4;
    // buf_write_uint32_be(buf, 2 + hei * (5 + line_wid) + 4);
    // crc_begin = buf_mark_pointer_w(buf);
    // buf_write_bytes(buf, "IDAT", 4);

    // buf_write_bytes(buf, "\x78\x1", 2);
    // for(size_t y = 0; y < hei; ++y) {
    //     buf_write_uint8(buf, y == hei - 1);
    //     buf_write_uint16_le(buf, line_wid);
    //     buf_write_uint16_le(buf, ~line_wid);

    //     adler_begin = buf_mark_pointer_w(buf);
    //     buf_write_uint8(buf, 0);
    //     buf_write_bytes(buf, bytes, line_wid - 1);
    //     adler_end = buf_mark_pointer_w(buf);
    //     adler32_update_bytes(&adler32, buf_take_pointer(buf, adler_begin), adler_end - adler_begin);
    // }
    // buf_write_uint32_be(buf, adler32);

    // crc_end = buf_mark_pointer_w(buf);
    // buf_write_uint32_be(buf, crc32(buf_take_pointer(buf, crc_begin), crc_end - crc_begin));

    Buffer buffer_zlib;
    zlib_buf_create(&buffer_zlib, zlib_cinfo_default, zlib_cm_default, zlib_level_fastest, zlib_dict_no, 0);

    png_write_IEND(png_buffer);
}
