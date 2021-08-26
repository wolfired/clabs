#ifndef ZLIB_H
#define ZLIB_h

typedef struct _ZLib {
    union {
        uint8_t cmf;
        struct {
            uint8_t cinfo : 4;
            uint8_t cm : 4;
        };
    };
    union {
        uint8_t flg;
        struct {
            uint8_t flevel : 2;
            uint8_t fdict : 1;
            uint8_t fcheck : 5;
        };
    };
    uint32_t dictid;
    uint8_t* compressed_data;
    uint32_t adler32;
} ZLib_, *ZLib;

void zlib_create(ZLib* p_thiz);
void zlib_delete(ZLib* p_thiz);

#endif
