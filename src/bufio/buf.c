#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "buf.h"

typedef struct _Buf {
    uint8_t*  bytes;
    ptrdiff_t pointer_r;
    ptrdiff_t pointer_w;
    size_t    capacity;
} Buf_, *Buf;

typedef union {
    int16_t  sint16;
    uint16_t uint16;
    uint8_t  int16_bytes[2];

    int32_t  sint32;
    uint32_t uint32;
    uint8_t  int32_bytes[4];

    int64_t  sint64;
    uint64_t uint64;
    uint8_t  int64_bytes[8];

    float   floatN;
    uint8_t floatN_bytes[sizeof(float)];

    double  doubleN;
    uint8_t doubleN_bytes[sizeof(double)];
} Number;

void buf_create(Buffer* p_thiz, size_t capacity) {
    Buf thiz = (Buf)malloc(sizeof(Buf_));

    thiz->bytes     = (uint8_t*)malloc(capacity);
    thiz->pointer_r = -1;
    thiz->pointer_w = -1;
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
    return ((Buf)thiz)->pointer_w - ((Buf)thiz)->pointer_r;
}

size_t buf_cap(Buffer thiz) {
    return ((Buf)thiz)->capacity;
}

ptrdiff_t buf_mark_pointer_w(Buffer thiz) {
    return ((Buf)thiz)->pointer_w + 1;
}
ptrdiff_t buf_mark_pointer_r(Buffer thiz) {
    return ((Buf)thiz)->pointer_r + 1;
}

uint8_t* buf_take_pointer(Buffer thiz, size_t skip) {
    return ((Buf)thiz)->bytes + skip;
}

static void buf_resize_cap(Buffer thiz, size_t count) {
    Buf buf = (Buf)thiz;

    if(buf->capacity <= buf->pointer_w + count) {
        buf->capacity += count * 2;
        buf->bytes = realloc(buf->bytes, buf->capacity);
    }
}

void buf_write_bytes(Buffer thiz, uint8_t* bytes, size_t count) {
    Buf buf = (Buf)thiz;

    buf_resize_cap(thiz, count);

    for(size_t i = 0; i < count; ++i) { buf->bytes[++buf->pointer_w] = bytes[i]; }
}

void buf_write_bytes_reverse(Buffer thiz, uint8_t* bytes, size_t count) {
    Buf buf = (Buf)thiz;

    buf_resize_cap(thiz, count);

    buf->pointer_w += count;

    for(size_t i = 0; i < count; ++i) { buf->bytes[buf->pointer_w - i] = bytes[i]; }
}

size_t buf_read_bytes(Buffer thiz, uint8_t* bytes, size_t count) {
    Buf buf = (Buf)thiz;

    count = buf_len(thiz) < count ? buf_len(thiz) : count;

    for(size_t i = 0; i < count; ++i) { bytes[i] = buf->bytes[++buf->pointer_r]; }

    return count;
}

size_t buf_read_bytes_reverse(Buffer thiz, uint8_t* bytes, size_t count) {
    Buf buf = (Buf)thiz;

    count = buf_len(thiz) < count ? buf_len(thiz) : count;

    buf->pointer_r += count;

    for(size_t i = 0; i < count; ++i) { bytes[i] = buf->bytes[buf->pointer_r - i]; }

    return count;
}

#if defined(_MSC_VER) || (defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__))
static void (*bele_write_bytes)(Buffer thiz, uint8_t* bytes, size_t count)          = buf_write_bytes_reverse;
static void (*bele_write_bytes_reverse)(Buffer thiz, uint8_t* bytes, size_t count)  = buf_write_bytes;
static size_t (*bele_read_bytes)(Buffer thiz, uint8_t* bytes, size_t count)         = buf_read_bytes_reverse;
static size_t (*bele_read_bytes_reverse)(Buffer thiz, uint8_t* bytes, size_t count) = buf_read_bytes;
#else
static void (*bele_write_bytes)(Buffer thiz, uint8_t* bytes, size_t count)          = buf_write_bytes;
static void (*bele_write_bytes_reverse)(Buffer thiz, uint8_t* bytes, size_t count)  = buf_write_bytes_reverse;
static size_t (*bele_read_bytes)(Buffer thiz, uint8_t* bytes, size_t count)         = buf_read_bytes;
static size_t (*bele_read_bytes_reverse)(Buffer thiz, uint8_t* bytes, size_t count) = buf_read_bytes_reverse;
#endif

void buf_write_uint8(Buffer thiz, uint8_t value) {
    buf_write_bytes(thiz, &value, 1);
}

uint8_t buf_read_uint8(Buffer thiz) {
    uint8_t value;
    buf_read_bytes(thiz, &value, 1);
    return value;
}

void buf_write_uint16_be(Buffer thiz, uint16_t value) {
    Number number = {uint16: value};
    bele_write_bytes(thiz, number.int16_bytes, 2);
}

uint16_t buf_read_uint16_be(Buffer thiz) {
    Number number;
    bele_read_bytes(thiz, number.int16_bytes, 2);
    return number.uint16;
}

void buf_write_uint16_le(Buffer thiz, uint16_t value) {
    Number number = {uint16: value};
    bele_write_bytes_reverse(thiz, number.int16_bytes, 2);
}

uint16_t buf_read_uint16_le(Buffer thiz) {
    Number number;
    bele_read_bytes_reverse(thiz, number.int16_bytes, 2);
    return number.uint16;
}

void buf_write_uint32_be(Buffer thiz, uint32_t value) {
    Number number = {uint32: value};
    bele_write_bytes(thiz, number.int32_bytes, 4);
}

uint32_t buf_read_uint32_be(Buffer thiz) {
    Number number;
    bele_read_bytes(thiz, number.int32_bytes, 4);
    return number.uint32;
}

void buf_write_uint32_le(Buffer thiz, uint32_t value) {
    Number number = {uint32: value};
    bele_write_bytes_reverse(thiz, number.int32_bytes, 4);
}

uint32_t buf_read_uint32_le(Buffer thiz) {
    Number number;
    bele_read_bytes_reverse(thiz, number.int32_bytes, 4);
    return number.uint32;
}

void buf_write_uint64_be(Buffer thiz, uint64_t value) {
    Number number = {uint64: value};
    bele_write_bytes(thiz, number.int64_bytes, 8);
}

uint64_t buf_read_uint64_be(Buffer thiz) {
    Number number;
    bele_read_bytes(thiz, number.int64_bytes, 8);
    return number.uint64;
}

void buf_write_uint64_le(Buffer thiz, uint64_t value) {
    Number number = {uint64: value};
    bele_write_bytes_reverse(thiz, number.int64_bytes, 8);
}
uint64_t buf_read_uint64_le(Buffer thiz) {
    Number number;
    bele_read_bytes_reverse(thiz, number.int64_bytes, 8);
    return number.uint64;
}

void buf_write_float_be(Buffer thiz, float value) {
    Number number = {floatN: value};
    bele_write_bytes(thiz, number.floatN_bytes, sizeof(float));
}

float buf_read_float_be(Buffer thiz) {
    Number number;
    bele_read_bytes(thiz, number.floatN_bytes, sizeof(float));
    return number.floatN;
}

void buf_write_float_le(Buffer thiz, float value) {
    Number number = {floatN: value};
    bele_write_bytes_reverse(thiz, number.floatN_bytes, sizeof(float));
}

float buf_read_float_le(Buffer thiz) {
    Number number;
    bele_read_bytes_reverse(thiz, number.floatN_bytes, sizeof(float));
    return number.floatN;
}

void buf_write_double_be(Buffer thiz, double value) {
    Number number = {doubleN: value};
    bele_write_bytes(thiz, number.doubleN_bytes, sizeof(double));
}

double buf_read_double_be(Buffer thiz) {
    Number number;
    bele_read_bytes(thiz, number.doubleN_bytes, sizeof(double));
    return number.doubleN;
}

void buf_write_double_le(Buffer thiz, double value) {
    Number number = {doubleN: value};
    bele_write_bytes_reverse(thiz, number.doubleN_bytes, sizeof(double));
}

double buf_read_double_le(Buffer thiz) {
    Number number;
    bele_read_bytes_reverse(thiz, number.doubleN_bytes, sizeof(double));
    return number.doubleN;
}
