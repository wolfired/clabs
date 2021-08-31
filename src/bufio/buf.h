#ifndef BUF_H
#define BUF_H

typedef void* Buffer;

void   buf_create(Buffer* p_thiz, size_t capacity);
void   buf_delete(Buffer* p_thiz);
size_t buf_len(Buffer thiz);
size_t buf_cap(Buffer thiz);

void   buf_write_bytes(Buffer thiz, uint8_t* bytes, size_t count);
size_t buf_read_bytes(Buffer thiz, uint8_t* bytes, size_t count);

void    buf_write_uint8(Buffer thiz, uint8_t value);
uint8_t buf_read_uint8(Buffer thiz);

void     buf_write_uint16_be(Buffer thiz, uint16_t value);
uint16_t buf_read_uint16_be(Buffer thiz);
void     buf_write_uint16_le(Buffer thiz, uint16_t value);
uint16_t buf_read_uint16_le(Buffer thiz);

void     buf_write_uint32_be(Buffer thiz, uint32_t value);
uint32_t buf_read_uint32_be(Buffer thiz);
void     buf_write_uint32_le(Buffer thiz, uint32_t value);
uint32_t buf_read_uint32_le(Buffer thiz);

void     buf_write_uint64_be(Buffer thiz, uint64_t value);
uint64_t buf_read_uint64_be(Buffer thiz);
void     buf_write_uint64_le(Buffer thiz, uint64_t value);
uint64_t buf_read_uint64_le(Buffer thiz);

void buf_write_float_be(Buffer thiz, float value);
float buf_read_float_be(Buffer thiz);
void buf_write_float_le(Buffer thiz, float value);
float buf_read_float_le(Buffer thiz);

void buf_write_double_be(Buffer thiz, double value);
double buf_read_double_be(Buffer thiz);
void buf_write_double_le(Buffer thiz, double value);
double buf_read_double_le(Buffer thiz);

#endif
