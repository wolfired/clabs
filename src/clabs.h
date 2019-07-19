#ifndef CLABS_H
#define CLABS_H

#include <stdio.h>
#include <quickjs-libc.h>

void trace(const char* msg);

void eval_binary(int argc, char **argv, unsigned char* raw, int raw_size);
void eval_source(int argc, char **argv, unsigned char* raw, int raw_size);

#endif
