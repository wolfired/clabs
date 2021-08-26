#ifndef BUF_H
#define BUF_H

typedef void* Buffer;

void buf_create(Buffer* p_thiz, size_t capacity);
void buf_delete(Buffer* p_thiz);
size_t buf_len(Buffer thiz);
size_t buf_cap(Buffer thiz);

#endif
