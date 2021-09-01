#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

typedef struct {
    size_t row;
    size_t col;
    float* values;
} * Matrix_f;

typedef struct {
    size_t    row;
    size_t    col;
    uint32_t* values;
} * Matrix_u;

#endif
