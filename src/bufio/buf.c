#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "buf.h"

typedef struct _Buf {
    uint8_t*  bytes;
    ptrdiff_t r_pointer;
    ptrdiff_t w_pointer;
    size_t    capacity;
} Buf_, *Buf;

void buf_create(Buffer* p_thiz, size_t capacity) {
    Buf thiz = (Buf)malloc(sizeof(Buf_));

    thiz->bytes     = (uint8_t*)malloc(capacity);
    thiz->r_pointer = 0;
    thiz->w_pointer = 0;
    thiz->capacity  = capacity;

    (*p_thiz) = (Buffer)thiz;
}

void buf_delete(Buffer* p_thiz) {
    Buf thiz = (Buf)*p_thiz;

    free(thiz->bytes);
    free(thiz);

    *p_thiz = NULL;
}

size_t buf_len(Buffer thiz) {
    return ((Buf)thiz)->w_pointer;
}

size_t buf_cap(Buffer thiz) {
    return ((Buf)thiz)->capacity;
}

void buf_write_bytes(Buffer thiz, uint8_t* bytes, size_t count) {
    Buf buf = (Buf)thiz;

    if(buf->w_pointer + count > buf->capacity) {
        size_t newcap = buf->capacity * 2;
        newcap        = newcap > buf->w_pointer + count ? newcap : (buf->w_pointer + count) * 2;
        void* vp      = realloc(buf->bytes, newcap);
        if(NULL == vp) { vp = malloc(newcap); }
        buf->bytes    = memcpy(vp, buf->bytes, buf->capacity);
        buf->capacity = newcap;
    }

    for(size_t i = 0; i < count; ++i) { buf->bytes[buf->w_pointer++] = bytes[i]; }
}
size_t buf_read_bytes(Buffer thiz, uint8_t* bytes, size_t count) {
    Buf buf = (Buf)thiz;

    size_t count_read = 0;

    for(size_t i = 0; i < count && buf->r_pointer < buf->w_pointer; ++i, ++buf->r_pointer) {
        bytes[i] = buf->bytes[buf->r_pointer];
        ++count_read;
    }

    return count_read < count ? count_read : count;
}

void buf_write_uint8(Buffer thiz, uint8_t value) {
    uint8_t bytes[sizeof(uint8_t)] = {value};
    buf_write_bytes(thiz, bytes, sizeof(uint8_t));
}
uint8_t buf_read_uint8(Buffer thiz) {
    uint8_t bytes[sizeof(uint8_t)];
    buf_read_bytes(thiz, bytes, sizeof(uint8_t));
    return bytes[0];
}

void buf_write_uint16_be(Buffer thiz, uint16_t value) {
    uint8_t bytes[sizeof(uint16_t)] = {value >> 8 & 0xff, value & 0xff};
    buf_write_bytes(thiz, bytes, sizeof(uint16_t));
}
uint16_t buf_read_uint16_be(Buffer thiz) {
    uint8_t bytes[sizeof(uint16_t)];
    buf_read_bytes(thiz, bytes, sizeof(uint16_t));
    return (uint16_t)bytes[0] << 8 | bytes[1];
}
void buf_write_uint16_le(Buffer thiz, uint16_t value) {
    uint8_t bytes[sizeof(uint16_t)] = {value & 0xff, value >> 8 & 0xff};
    buf_write_bytes(thiz, bytes, sizeof(uint16_t));
}
uint16_t buf_read_uint16_le(Buffer thiz) {
    uint8_t bytes[sizeof(uint16_t)];
    buf_read_bytes(thiz, bytes, sizeof(uint16_t));
    return (uint16_t)bytes[1] << 8 | bytes[0];
}

void buf_write_uint32_be(Buffer thiz, uint32_t value) {
    uint8_t bytes[sizeof(uint32_t)] = {value >> 24 & 0xff, value >> 16 & 0xff, value >> 8 & 0xff, value & 0xff};
    buf_write_bytes(thiz, bytes, sizeof(uint32_t));
}
uint32_t buf_read_uint32_be(Buffer thiz) {
    uint8_t bytes[sizeof(uint32_t)];
    buf_read_bytes(thiz, bytes, sizeof(uint32_t));
    return (uint32_t)bytes[0] << 24 | (uint32_t)bytes[1] << 16 | (uint32_t)bytes[2] << 8 | bytes[3];
}
void buf_write_uint32_le(Buffer thiz, uint32_t value) {
    uint8_t bytes[sizeof(uint32_t)] = {value & 0xff, value >> 8 & 0xff, value >> 16 & 0xff, value >> 24 & 0xff};
    buf_write_bytes(thiz, bytes, sizeof(uint32_t));
}
uint32_t buf_read_uint32_le(Buffer thiz) {
    uint8_t bytes[sizeof(uint32_t)];
    buf_read_bytes(thiz, bytes, sizeof(uint32_t));
    return (uint32_t)bytes[3] << 24 | (uint32_t)bytes[2] << 16 | (uint32_t)bytes[1] << 8 | bytes[0];
}

void buf_write_uint64_be(Buffer thiz, uint64_t value) {
    uint8_t bytes[sizeof(uint64_t)] = {value >> 56 & 0xff, value >> 48 & 0xff, value >> 40 & 0xff, value >> 32 & 0xff, value >> 24 & 0xff, value >> 16 & 0xff, value >> 8 & 0xff, value & 0xff};
    buf_write_bytes(thiz, bytes, sizeof(uint64_t));
}
uint64_t buf_read_uint64_be(Buffer thiz) {
    uint8_t bytes[sizeof(uint64_t)];
    buf_read_bytes(thiz, bytes, sizeof(uint64_t));
    return (uint64_t)bytes[0] << 56 | (uint64_t)bytes[1] << 48 | (uint64_t)bytes[2] << 40 | (uint64_t)bytes[3] << 32 | (uint64_t)bytes[4] << 24 | (uint64_t)bytes[5] << 16 | (uint64_t)bytes[6] << 8 | bytes[7];
}
void buf_write_uint64_le(Buffer thiz, uint64_t value) {
    uint8_t bytes[sizeof(uint64_t)] = {value & 0xff, value >> 8 & 0xff, value >> 16 & 0xff, value >> 24 & 0xff, value >> 32 & 0xff, value >> 40 & 0xff, value >> 48 & 0xff, value >> 56 & 0xff};
    buf_write_bytes(thiz, bytes, sizeof(uint64_t));
}
uint64_t buf_read_uint64_le(Buffer thiz) {
    uint8_t bytes[sizeof(uint64_t)];
    buf_read_bytes(thiz, bytes, sizeof(uint64_t));
    return (uint64_t)bytes[7] << 56 | (uint64_t)bytes[6] << 48 | (uint64_t)bytes[5] << 40 | (uint64_t)bytes[4] << 32 | (uint64_t)bytes[3] << 24 | (uint64_t)bytes[2] << 16 | (uint64_t)bytes[1] << 8 | bytes[0];
}
