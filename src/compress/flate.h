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

void deflate_block(BFINAL is_final, BTYPE type, Buffer compress, Buffer compressed);

#endif
