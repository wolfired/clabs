#include <locale.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "math/linear_algebra.h"

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    // clang-format off
    Matrix dst = {.row = 4, .col = 4, .raw = {[15] = 0}};
    Matrix src = {.row = 4, .col = 4, .raw = {
        0x0,0x1,0x2,0x3,
        0x4,0x5,0x6,0x7,
        0x8,0x9,0xa,0xb,
        0xc,0xd,0xe,0xf,
    }};
    Matrix left = {.row = 4, .col = 4, .raw = {
        0,1,2,3,
        0,1,2,3,
        0,1,2,3,
        0,1,2,3,
    }};
    Matrix right = {.row = 4, .col = 4, .raw = {
        0,1,2,3,
        0,1,2,3,
        0,1,2,3,
        0,1,2,3,
    }};
    // clang-format on

    matrix_print(&src);

    return EXIT_SUCCESS;
}
