#ifndef ZLIB_H
#define ZLIB_h

typedef enum {
    zlib_cm_default = 0x08,
} ZLibCM;

typedef enum {
    zlib_cinfo_default = 0x07,
} ZLibCINFO;

typedef enum {
    zlib_level_fastest = 0b00, // compressor used fastest algorithm
    zlib_level_fast    = 0b01, // compressor used fast algorithm
    zlib_level_default = 0b10, // compressor used default algorithm
    zlib_level_best    = 0b11, // compressor used maximum compression, slowest algorithm
} ZLibFLEVEL;

typedef enum {
    zlib_dict_no  = 0b0,
    zlib_dict_yes = 0b1,
} ZLibFDICT;

typedef struct {
    union {
        uint8_t cmf;
        struct {
            ZLibCINFO cinfo : 4;
            ZLibCM    cm : 4;
        };
    };
    union {
        uint8_t flg;
        struct {
            ZLibFLEVEL flevel : 2;
            ZLibFDICT  fdict : 1;
            uint8_t    fcheck : 5;
        };
    };
} ZLibHeader;

void zlib_buf_create(Buffer* p_thiz, ZLibCINFO cinfo, ZLibCM cm, ZLibFLEVEL flevel, ZLibFDICT fdict, uint32_t dictid);
void zlib_buf_delete(Buffer* p_thiz);
void zlib_buf_write_compressed_data(Buffer zip_buffer, Buffer dat_buffer);
#endif
