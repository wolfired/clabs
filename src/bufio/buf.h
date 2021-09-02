#ifndef BUF_H
#define BUF_H

typedef void* Buffer;

void buf_create(Buffer* p_buffer, size_t capacity);
void buf_delete(Buffer* p_buffer);

void buf_reset(Buffer buffer);
size_t buf_len(Buffer buffer);
size_t buf_cap(Buffer buffer);

ptrdiff_t buf_mark_pointer_offset_w(Buffer thiz);
ptrdiff_t buf_mark_pointer_offset_r(Buffer thiz);
uint8_t*  buf_take_pointer(Buffer thiz, size_t skip);

void buf_write_bytes(Buffer buffer, uint8_t* bytes, size_t count);
void buf_write_bytes_reverse(Buffer buffer, uint8_t* bytes, size_t count);
void buf_write_buffer(Buffer buffer_dst, Buffer buffer_src);

size_t buf_read_bytes(Buffer buffer, uint8_t* bytes, size_t count);
size_t buf_read_bytes_reverse(Buffer buffer, uint8_t* bytes, size_t count);

void    buf_write_uint8(Buffer buffer, uint8_t value);
uint8_t buf_read_uint8(Buffer buffer);

void     buf_write_uint16_be(Buffer buffer, uint16_t value);
uint16_t buf_read_uint16_be(Buffer buffer);
void     buf_write_uint16_le(Buffer buffer, uint16_t value);
uint16_t buf_read_uint16_le(Buffer buffer);

void     buf_write_uint32_be(Buffer buffer, uint32_t value);
uint32_t buf_read_uint32_be(Buffer buffer);
void     buf_write_uint32_le(Buffer buffer, uint32_t value);
uint32_t buf_read_uint32_le(Buffer buffer);

void     buf_write_uint64_be(Buffer buffer, uint64_t value);
uint64_t buf_read_uint64_be(Buffer buffer);
void     buf_write_uint64_le(Buffer buffer, uint64_t value);
uint64_t buf_read_uint64_le(Buffer buffer);

void  buf_write_float_be(Buffer buffer, float value);
float buf_read_float_be(Buffer buffer);
void  buf_write_float_le(Buffer buffer, float value);
float buf_read_float_le(Buffer buffer);

void   buf_write_double_be(Buffer buffer, double value);
double buf_read_double_be(Buffer buffer);
void   buf_write_double_le(Buffer buffer, double value);
double buf_read_double_le(Buffer buffer);

#endif
