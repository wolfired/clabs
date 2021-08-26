#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

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
    thiz->r_pointer = -1;
    thiz->w_pointer = -1;
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
    return ((Buf)thiz)->w_pointer + 1;
}

size_t buf_cap(Buffer thiz) {
    return ((Buf)thiz)->capacity;
}
