#ifndef ZLIB_H
#define ZLIB_h

typedef enum {
    zlib_cm_default = 0x08,
} ZLibCM;

typedef enum {
    zlib_cinfo_default = 0x70,
} ZLibCINFO;

typedef enum {
    zlib_level_fastest = 0b00000000, // compressor used fastest algorithm
    zlib_level_fast    = 0b01000000, // compressor used fast algorithm
    zlib_level_default = 0b10000000, // compressor used default algorithm
    zlib_level_best    = 0b11000000, // compressor used maximum compression, slowest algorithm
} ZLibFLEVEL;

typedef enum {
    zlib_dict_no  = 0b000000,
    zlib_dict_yes = 0b100000,
} ZLibFDICT;

// typedef struct {
//     union {
//         uint8_t cmf;
//         struct {
//             ZLibCM    cm : 4;
//             ZLibCINFO cinfo : 4;
//         };
//     };
//     union {
//         uint8_t flg;
//         struct {
//             uint8_t    fcheck : 5;
//             ZLibFDICT  fdict : 1;
//             ZLibFLEVEL flevel : 2;
//         };
//     };
// } ZLibHeader;

void zlib_buf_create(Buffer* p_thiz, ZLibCINFO cinfo, ZLibCM cm, ZLibFLEVEL flevel, ZLibFDICT fdict, uint32_t dictid);
void zlib_buf_delete(Buffer* p_thiz);
void zlib_buf_write_compressed_data(Buffer buffer_zlib, Buffer buffer_compressed);
#endif
