#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "bufio/buf.h"

typedef struct {
    uint8_t*  pointer_raw_data;
    ptrdiff_t pointer_offset_r;
    ptrdiff_t pointer_offset_w;
    size_t    capacity;
} Buf, *BufPtr;

typedef union {
    int16_t  sint16;
    uint16_t uint16;
    uint8_t  int16_bytes[sizeof(uint16_t)];

    int32_t  sint32;
    uint32_t uint32;
    uint8_t  int32_bytes[sizeof(uint32_t)];

    int64_t  sint64;
    uint64_t uint64;
    uint8_t  int64_bytes[sizeof(uint64_t)];

    float   floatN;
    uint8_t floatN_bytes[sizeof(float)];

    double  doubleN;
    uint8_t doubleN_bytes[sizeof(double)];
} Number;

void buf_create(Buffer* p_buffer, size_t capacity) {
    BufPtr buf = (BufPtr)malloc(sizeof(Buf));

    buf->capacity         = capacity;
    buf->pointer_raw_data = (uint8_t*)malloc(buf->capacity);
    buf->pointer_offset_r = -1;
    buf->pointer_offset_w = -1;

    (*p_buffer) = (Buffer)buf;
}

void buf_delete(Buffer* p_buffer) {
    BufPtr buf = (BufPtr)*p_buffer;

    free(buf->pointer_raw_data);
    free(buf);

    *p_buffer = NULL;
}

size_t buf_len(Buffer buffer) {
    return ((BufPtr)buffer)->pointer_offset_w - ((BufPtr)buffer)->pointer_offset_r;
}

size_t buf_cap(Buffer buffer) {
    return ((BufPtr)buffer)->capacity;
}

ptrdiff_t buf_mark_pointer_offset_w(Buffer thiz) {
    return ((BufPtr)thiz)->pointer_offset_w + 1;
}
ptrdiff_t buf_mark_pointer_offset_r(Buffer thiz) {
    return ((BufPtr)thiz)->pointer_offset_r + 1;
}

uint8_t* buf_take_pointer(Buffer thiz, size_t skip) {
    return ((BufPtr)thiz)->pointer_raw_data + skip;
}

static void buf_resize_cap(BufPtr buf, size_t count) {
    if(buf->capacity <= buf->pointer_offset_w + count) {
        buf->capacity += count * 2;
        buf->pointer_raw_data = realloc(buf->pointer_raw_data, buf->capacity);
    }
}

static inline bool is_big_endian() {
    static union {
        uint16_t value;
        uint8_t  bytes[2];
    } checker = {value: 0xFF00};
    return 0xFF == checker.bytes[0];
}

void buf_write_bytes(Buffer buffer, uint8_t* bytes, size_t count) {
    BufPtr buf = (BufPtr)buffer;

    buf_resize_cap(buf, count);

    for(size_t i = 0; i < count; ++i) { buf->pointer_raw_data[++buf->pointer_offset_w] = bytes[i]; }
}

void buf_write_bytes_reverse(Buffer buffer, uint8_t* bytes, size_t count) {
    BufPtr buf = (BufPtr)buffer;

    buf_resize_cap(buf, count);

    buf->pointer_offset_w += count;

    for(size_t i = 0; i < count; ++i) { buf->pointer_raw_data[buf->pointer_offset_w - i] = bytes[i]; }
}

void buf_write_buffer(Buffer buffer_dst, Buffer buffer_src) {
    BufPtr buf_src = (BufPtr)buffer_src;

    buf_write_bytes(buffer_dst, buf_src->pointer_raw_data + buf_src->pointer_offset_r, buf_len(buffer_src));
}

size_t buf_read_bytes(Buffer buffer, uint8_t* bytes, size_t count) {
    BufPtr buf = (BufPtr)buffer;

    count = buf_len(buf) < count ? buf_len(buf) : count;

    for(size_t i = 0; i < count; ++i) { bytes[i] = buf->pointer_raw_data[++buf->pointer_offset_r]; }

    return count;
}

size_t buf_read_bytes_reverse(Buffer buffer, uint8_t* bytes, size_t count) {
    BufPtr buf = (BufPtr)buffer;

    count = buf_len(buffer) < count ? buf_len(buffer) : count;

    buf->pointer_offset_r += count;

    for(size_t i = 0; i < count; ++i) { bytes[i] = buf->pointer_raw_data[buf->pointer_offset_r - i]; }

    return count;
}

void buf_write_uint8(Buffer buffer, uint8_t value) {
    buf_write_bytes(buffer, &value, 1);
}

uint8_t buf_read_uint8(Buffer buffer) {
    uint8_t value;
    buf_read_bytes(buffer, &value, 1);
    return value;
}

void buf_write_uint16_be(Buffer buffer, uint16_t value) {
    Number number = {uint16: value};
    if(is_big_endian()) {
        buf_write_bytes(buffer, number.int16_bytes, sizeof(uint16_t));
    } else {
        buf_write_bytes_reverse(buffer, number.int16_bytes, sizeof(uint16_t));
    }
}

uint16_t buf_read_uint16_be(Buffer buffer) {
    Number number;
    if(is_big_endian()) {
        buf_read_bytes(buffer, number.int16_bytes, sizeof(uint16_t));
    } else {
        buf_read_bytes_reverse(buffer, number.int16_bytes, sizeof(uint16_t));
    }
    return number.uint16;
}

void buf_write_uint16_le(Buffer buffer, uint16_t value) {
    Number number = {uint16: value};
    if(is_big_endian()) {
        buf_write_bytes_reverse(buffer, number.int16_bytes, sizeof(uint16_t));
    } else {
        buf_write_bytes(buffer, number.int16_bytes, sizeof(uint16_t));
    }
}

uint16_t buf_read_uint16_le(Buffer buffer) {
    Number number;
    if(is_big_endian()) {
        buf_read_bytes_reverse(buffer, number.int16_bytes, sizeof(uint16_t));
    } else {
        buf_read_bytes(buffer, number.int16_bytes, sizeof(uint16_t));
    }
    return number.uint16;
}

void buf_write_uint32_be(Buffer buffer, uint32_t value) {
    Number number = {uint32: value};
    if(is_big_endian()) {
        buf_write_bytes(buffer, number.int32_bytes, sizeof(uint32_t));
    } else {
        buf_write_bytes_reverse(buffer, number.int32_bytes, sizeof(uint32_t));
    }
}

uint32_t buf_read_uint32_be(Buffer buffer) {
    Number number;
    if(is_big_endian()) {
        buf_read_bytes(buffer, number.int32_bytes, sizeof(uint32_t));
    } else {
        buf_read_bytes_reverse(buffer, number.int32_bytes, sizeof(uint32_t));
    }
    return number.uint32;
}

void buf_write_uint32_le(Buffer buffer, uint32_t value) {
    Number number = {uint32: value};
    if(is_big_endian()) {
        buf_write_bytes_reverse(buffer, number.int32_bytes, sizeof(uint32_t));
    } else {
        buf_write_bytes(buffer, number.int32_bytes, sizeof(uint32_t));
    }
}

uint32_t buf_read_uint32_le(Buffer buffer) {
    Number number;
    if(is_big_endian()) {
        buf_read_bytes_reverse(buffer, number.int32_bytes, sizeof(uint32_t));
    } else {
        buf_read_bytes(buffer, number.int32_bytes, sizeof(uint32_t));
    }
    return number.uint32;
}

void buf_write_uint64_be(Buffer buffer, uint64_t value) {
    Number number = {uint64: value};
    if(is_big_endian()) {
        buf_write_bytes(buffer, number.int64_bytes, sizeof(uint64_t));
    } else {
        buf_write_bytes_reverse(buffer, number.int64_bytes, sizeof(uint64_t));
    }
}

uint64_t buf_read_uint64_be(Buffer buffer) {
    Number number;
    if(is_big_endian()) {
        buf_read_bytes(buffer, number.int64_bytes, sizeof(uint64_t));
    } else {
        buf_read_bytes_reverse(buffer, number.int64_bytes, sizeof(uint64_t));
    }
    return number.uint64;
}

void buf_write_uint64_le(Buffer buffer, uint64_t value) {
    Number number = {uint64: value};
    if(is_big_endian()) {
        buf_write_bytes_reverse(buffer, number.int64_bytes, sizeof(uint64_t));
    } else {
        buf_write_bytes(buffer, number.int64_bytes, sizeof(uint64_t));
    }
}
uint64_t buf_read_uint64_le(Buffer buffer) {
    Number number;
    if(is_big_endian()) {
        buf_read_bytes_reverse(buffer, number.int64_bytes, sizeof(uint64_t));
    } else {
        buf_read_bytes(buffer, number.int64_bytes, sizeof(uint64_t));
    }
    return number.uint64;
}

void buf_write_float_be(Buffer buffer, float value) {
    Number number = {floatN: value};
    if(is_big_endian()) {
        buf_write_bytes(buffer, number.floatN_bytes, sizeof(float));
    } else {
        buf_write_bytes_reverse(buffer, number.floatN_bytes, sizeof(float));
    }
}

float buf_read_float_be(Buffer buffer) {
    Number number;
    if(is_big_endian()) {
        buf_read_bytes(buffer, number.floatN_bytes, sizeof(float));
    } else {
        buf_read_bytes_reverse(buffer, number.floatN_bytes, sizeof(float));
    }
    return number.floatN;
}

void buf_write_float_le(Buffer buffer, float value) {
    Number number = {floatN: value};
    if(is_big_endian()) {
        buf_write_bytes_reverse(buffer, number.floatN_bytes, sizeof(float));
    } else {
        buf_write_bytes(buffer, number.floatN_bytes, sizeof(float));
    }
}

float buf_read_float_le(Buffer buffer) {
    Number number;
    if(is_big_endian()) {
        buf_read_bytes_reverse(buffer, number.floatN_bytes, sizeof(float));
    } else {
        buf_read_bytes(buffer, number.floatN_bytes, sizeof(float));
    }
    return number.floatN;
}

void buf_write_double_be(Buffer buffer, double value) {
    Number number = {doubleN: value};
    if(is_big_endian()) {
        buf_write_bytes(buffer, number.doubleN_bytes, sizeof(double));
    } else {
        buf_write_bytes_reverse(buffer, number.doubleN_bytes, sizeof(double));
    }
}

double buf_read_double_be(Buffer buffer) {
    Number number;
    if(is_big_endian()) {
        buf_read_bytes(buffer, number.doubleN_bytes, sizeof(double));
    } else {
        buf_read_bytes_reverse(buffer, number.doubleN_bytes, sizeof(double));
    }
    return number.doubleN;
}

void buf_write_double_le(Buffer buffer, double value) {
    Number number = {doubleN: value};
    if(is_big_endian()) {
        buf_write_bytes_reverse(buffer, number.doubleN_bytes, sizeof(double));
    } else {
        buf_write_bytes(buffer, number.doubleN_bytes, sizeof(double));
    }
}

double buf_read_double_le(Buffer buffer) {
    Number number;
    if(is_big_endian()) {
        buf_read_bytes_reverse(buffer, number.doubleN_bytes, sizeof(double));
    } else {
        buf_read_bytes(buffer, number.doubleN_bytes, sizeof(double));
    }
    return number.doubleN;
}
