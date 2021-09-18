#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "math/linear_algebra.h"

void matrix_raw_print(const float* dst, int32_t row, int32_t col) {
    assert(NULL != dst);

    for(int32_t i = 0; i < row * col; ++i) {
        if(0 < i && 0 == (i % col)) { printf("\n"); }
        printf("%11.2f", dst[i]);
    }

    printf("\n");
}

void matrix_raw_init(float value, float* dst, int32_t row, int32_t col) {
    assert(NULL != dst);

    for(int32_t i = 0; i < row * col; ++i) { dst[i] = value; }
}

void matrix_raw_add(float* left, const float* right, int32_t row, int32_t col) {
    matrix_raw_add_to(left, left, right, row, col);
}

void matrix_raw_add_to(float* dst, const float* left, const float* right, int32_t row, int32_t col) {
    assert(NULL != left);
    assert(NULL != right);

    for(int32_t i = 0; i < row * col; ++i) { dst[i] = left[i] + right[i]; }
}

void matrix_raw_sub(float* left, const float* right, int32_t row, int32_t col) {
    matrix_raw_sub_to(left, left, right, row, col);
}

void matrix_raw_sub_to(float* dst, const float* left, const float* right, int32_t row, int32_t col) {
    assert(NULL != left);
    assert(NULL != right);

    for(int32_t i = 0; i < row * col; ++i) { dst[i] = left[i] - right[i]; }
}

void matrix_raw_mul(float* left, int32_t left_row, int32_t left_col, const float* right, int32_t right_row, int32_t right_col) {
    size_t size = sizeof(float) * left_row * right_col;
    float* temp = malloc(size);

    matrix_raw_mul_to(temp, left, left_row, left_col, right, right_row, right_col);

    memcpy(left, temp, size), free(temp);
}

void matrix_raw_mul_to(float* dst, const float* left, int32_t left_row, int32_t left_col, const float* right, int32_t right_row, int32_t right_col) {
    assert(NULL != dst);
    assert(NULL != left);
    assert(NULL != right);
    assert(left_col == right_row);

    for(int32_t r = 0; r < left_row; ++r) {
        for(int32_t c = 0; c < right_col; ++c) {
            for(int32_t i = 0; i < right_row; ++i) { dst[r * right_col + c] += left[r * left_col + i] * right[i * right_col + c]; }
        }
    }
}

void matrix_raw_scale(float factor, float* dst, int32_t row, int32_t col) {
    matrix_raw_scale_to(factor, dst, dst, row, col);
}

void matrix_raw_scale_to(float factor, float* dst, const float* src, int32_t row, int32_t col) {
    assert(NULL != dst);
    assert(NULL != src);

    for(int32_t i = 0; i < row * col; ++i) { dst[i] = factor * src[i]; }
}

void matrix_raw_transpose(float* dst, int32_t row, int32_t col) {
    size_t size = sizeof(float) * row * col;
    float* temp = malloc(size);

    matrix_raw_transpose_to(temp, dst, row, col);

    memcpy(dst, temp, size), free(temp);
}

void matrix_raw_transpose_to(float* dst, const float* src, int32_t row, int32_t col) {
    assert(NULL != dst);
    assert(NULL != src);

    for(int32_t r = 0; r < row; ++r) {
        for(int32_t c = 0; c < col; ++c) { dst[c * row + r] = src[r * col + c]; }
    }
}

void matrix_create(MatrixPtr* hold, int32_t row, int32_t col) {
    assert(NULL == *hold);

    *hold        = malloc(sizeof(**hold) * row * col * sizeof(float));
    (*hold)->row = row;
    (*hold)->col = col;

    matrix_init(0, *hold);
}

void matrix_destory(MatrixPtr* hold) {
    assert(NULL != *hold);

    free(*hold);

    *hold = NULL;
}

void matrix_print(MatrixPtr dst) {
    matrix_raw_print(dst->raw, dst->row, dst->col);
}

void matrix_init(float value, MatrixPtr dst) {
    matrix_raw_init(value, dst->raw, dst->row, dst->col);
}

void matrix_add(MatrixPtr left, MatrixPtr right) {
    matrix_raw_add(left->raw, right->raw, left->row, left->col);
}

void matrix_add_to(MatrixPtr dst, MatrixPtr left, MatrixPtr right) {
    matrix_raw_add_to(dst->raw, left->raw, right->raw, left->row, left->col);
}

void matrix_sub(MatrixPtr left, MatrixPtr right) {
    matrix_raw_sub(left->raw, right->raw, left->row, left->col);
}

void matrix_sub_to(MatrixPtr dst, MatrixPtr left, MatrixPtr right) {
    matrix_raw_sub_to(dst->raw, left->raw, right->raw, left->row, left->col);
}
