#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

typedef struct {
    int32_t row;
    int32_t col;
    float   raw[];
} Matrix, *MatrixPtr;

void matrix_raw_print(const float* dst, int32_t row, int32_t col);
void matrix_raw_init(float value, float* dst, int32_t row, int32_t col);
void matrix_raw_add(float* left, const float* right, int32_t row, int32_t col);
void matrix_raw_add_to(float* dst, const float* left, const float* right, int32_t row, int32_t col);
void matrix_raw_sub(float* left, const float* right, int32_t row, int32_t col);
void matrix_raw_sub_to(float* dst, const float* left, const float* right, int32_t row, int32_t col);
void matrix_raw_mul(float* left, int32_t left_row, int32_t left_col, const float* right, int32_t right_row, int32_t right_col);
void matrix_raw_mul_to(float* dst, const float* left, int32_t left_row, int32_t left_col, const float* right, int32_t right_row, int32_t right_col);
void matrix_raw_scale(float factor, float* dst, int32_t row, int32_t col);
void matrix_raw_scale_to(float factor, float* dst, const float* src, int32_t row, int32_t col);
void matrix_raw_transpose(float* dst, int32_t row, int32_t col);
void matrix_raw_transpose_to(float* dst, const float* src, int32_t row, int32_t col);

void matrix_print(MatrixPtr dst);
void matrix_init(float value, MatrixPtr dst);
void matrix_add(MatrixPtr left, MatrixPtr right);
void matrix_add_to(MatrixPtr dst, MatrixPtr left, MatrixPtr right);
void matrix_sub(MatrixPtr left, MatrixPtr right);
void matrix_sub_to(MatrixPtr dst, MatrixPtr left, MatrixPtr right);

#endif
