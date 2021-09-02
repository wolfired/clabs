#ifndef FLATE_H
#define FLATE_H

typedef enum {
    deflate_type_no       = 0b000, // no compression
    deflate_type_fixed    = 0b010, // compressed with fixed Huffman codes
    deflate_type_dynamic  = 0b100, // compressed with dynamic Huffman codes
    deflate_type_reserved = 0b110, // error
} BTYPE;

typedef enum {
    deflate_final_no  = 0b0,
    deflate_final_yes = 0b1,
} BFINAL;

void deflate_write_buffer(BFINAL is_final, BTYPE type, Buffer buffer_uncompress, Buffer buffer_compressed);
void deflate_write_bytes(BFINAL is_final, BTYPE type, uint8_t* bytes, size_t bytes_count, Buffer buffer_compressed);

#endif
