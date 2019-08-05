#ifndef QJS_H
#define QJS_H

#include <quickjs-libc.h>

void eval_binary(int argc, char **argv, unsigned char* raw, int raw_size);
void eval_source(int argc, char **argv, unsigned char* raw, int raw_size);

#endif
