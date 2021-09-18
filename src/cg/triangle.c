#include <stdbool.h>
#include <stdint.h>

#include "line.h"

#include "triangle.h"

static void standardize(int32_t* x0, int32_t* y0, int32_t* x1, int32_t* y1, int32_t* x2, int32_t* y2) {
    if (*y0 > *y1) {
        *x0 ^= *x1, *x1 ^= *x0, *x0 ^= *x1;
        *y0 ^= *y1, *y1 ^= *y0, *y0 ^= *y1;
    }
    if (*y0 > *y2) {
        *x0 ^= *x2, *x2 ^= *x0, *x0 ^= *x2;
        *y0 ^= *y2, *y2 ^= *y0, *y0 ^= *y2;
    }
    if (*y1 > *y2) {
        *x1 ^= *x2, *x2 ^= *x1, *x1 ^= *x2;
        *y1 ^= *y2, *y2 ^= *y1, *y1 ^= *y2;
    }
    if (*y0 == *y1) {
        if (*x0 > *x1) {
            *x0 ^= *x1, *x1 ^= *x0, *x0 ^= *x1;
            *y0 ^= *y1, *y1 ^= *y0, *y0 ^= *y1;
        }
    } else if (*y1 == *y2) {
        if (*x1 < *x2) {
            *x1 ^= *x2, *x2 ^= *x1, *x1 ^= *x2;
            *y1 ^= *y2, *y2 ^= *y1, *y1 ^= *y2;
        }
    } else {
    }
}

void triangle_fill(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
    standardize(&x0, &y0, &x1, &y1, &x2, &y2);




    //
    //
}
