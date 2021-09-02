#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bufio/buf.h"
#include "compress/flate.h"
#include "compress/zlib.h"
#include "hash/adler32.h"
#include "hash/crc32.h"

#include "image/png.h"

void png_write_magic(Buffer png_buffer) {
    uint8_t magic[] = {137, 80, 78, 71, 13, 10, 26, 10};
    buf_write_bytes(png_buffer, magic, sizeof(magic));
}

void png_write_IHDR(Buffer png_buffer, uint32_t wid, uint32_t hei) {
    buf_write_uint32_be(png_buffer, 13);
    ptrdiff_t crc_begin = buf_mark_pointer_offset_w(png_buffer);
    buf_write_bytes(png_buffer, "IHDR", 4);
    buf_write_uint32_be(png_buffer, wid);
    buf_write_uint32_be(png_buffer, hei);
    buf_write_uint8(png_buffer, 0x8);
    buf_write_uint8(png_buffer, 0x6);
    buf_write_uint8(png_buffer, 0x0);
    buf_write_uint8(png_buffer, 0x0);
    buf_write_uint8(png_buffer, 0x0);
    ptrdiff_t crc_end = buf_mark_pointer_offset_w(png_buffer);
    buf_write_uint32_be(png_buffer, crc32(buf_take_pointer(png_buffer, crc_begin), crc_end - crc_begin));
}

void png_write_IEND(Buffer png_buffer) {
    buf_write_uint32_be(png_buffer, 0);
    ptrdiff_t crc_begin = buf_mark_pointer_offset_w(png_buffer);
    buf_write_bytes(png_buffer, "IEND", 4);
    ptrdiff_t crc_end = buf_mark_pointer_offset_w(png_buffer);
    buf_write_uint32_be(png_buffer, crc32(buf_take_pointer(png_buffer, crc_begin), crc_end - crc_begin));
}

void print_bytes(Buffer buffer) {
    uint8_t* p = buf_take_pointer(buffer, 0);
    size_t   l = buf_len(buffer);
    for(size_t i = 0; i < l; ++i) { printf("%02x ", p[i]); }
    printf("\n");
}

void png_encode_pixel_bytes(Buffer png_buffer, uint32_t wid, uint32_t hei, uint8_t* pixel_bytes) {
    // ptrdiff_t crc_begin = -1;
    // ptrdiff_t crc_end   = -1;

    png_write_magic(png_buffer);
    png_write_IHDR(png_buffer, wid, hei);

    // uint32_t  adler32     = 1;
    // ptrdiff_t adler_begin = -1;
    // ptrdiff_t adler_end   = -1;

    // uint16_t line_wid = 1 + wid * 4;
    // buf_write_uint32_be(buf, 2 + hei * (5 + line_wid) + 4);
    // crc_begin = buf_mark_pointer_offset_w(buf);
    // buf_write_bytes(buf, "IDAT", 4);

    // buf_write_bytes(buf, "\x78\x1", 2);
    // for(size_t y = 0; y < hei; ++y) {
    //     buf_write_uint8(buf, y == hei - 1);
    //     buf_write_uint16_le(buf, line_wid);
    //     buf_write_uint16_le(buf, ~line_wid);

    //     adler_begin = buf_mark_pointer_offset_w(buf);
    //     buf_write_uint8(buf, 0);
    //     buf_write_bytes(buf, bytes, line_wid - 1);
    //     adler_end = buf_mark_pointer_offset_w(buf);
    //     adler32_update_bytes(&adler32, buf_take_pointer(buf, adler_begin), adler_end - adler_begin);
    // }
    // buf_write_uint32_be(buf, adler32);

    // crc_end = buf_mark_pointer_offset_w(buf);
    // buf_write_uint32_be(buf, crc32(buf_take_pointer(buf, crc_begin), crc_end - crc_begin));

    uint32_t adler32 = 1;

    buf_write_uint32_be(png_buffer, 2 + hei * (1 + 2 + 2 + (1 + wid * 4)) + 4);
    ptrdiff_t crc_begin = buf_mark_pointer_offset_w(png_buffer);
    buf_write_bytes(png_buffer, "IDAT", 4);

    Buffer buffer_zlib;
    zlib_buf_create(&buffer_zlib, zlib_cinfo_default, zlib_cm_default, zlib_level_fastest, zlib_dict_no, 0);

    Buffer buffer_uncompress;
    buf_create(&buffer_uncompress, 0);

    Buffer buffer_compressed;
    buf_create(&buffer_compressed, 0);

    for(size_t y = 0; y < hei; ++y) {
        buf_reset(buffer_uncompress);

        buf_write_uint8(buffer_uncompress, 0);
        buf_write_bytes(buffer_uncompress, pixel_bytes + y * wid * 4, wid * 4);

        adler32_update_bytes(&adler32, buf_take_pointer(buffer_uncompress, 0), buf_len(buffer_uncompress));

        deflate_write_buffer(y == hei - 1 ? deflate_final_yes : deflate_final_no, deflate_type_no, buffer_uncompress, buffer_compressed);
    }
    buf_write_buffer(buffer_zlib, buffer_compressed);
    buf_write_buffer(png_buffer, buffer_zlib);
    buf_write_uint32_be(png_buffer, adler32);
    ptrdiff_t crc_end = buf_mark_pointer_offset_w(png_buffer);
    buf_write_uint32_be(png_buffer, crc32(buf_take_pointer(png_buffer, crc_begin), crc_end - crc_begin));

    buf_delete(&buffer_uncompress);
    buf_delete(&buffer_compressed);
    zlib_buf_delete(&buffer_zlib);

    png_write_IEND(png_buffer);
}
