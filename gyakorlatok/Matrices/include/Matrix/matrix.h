#ifndef MATRIX_H_
#define MATRIX_H_

void init_null_matrix(float matrix[3][3]);

void init_identity_matrix(float matrix[3][3]);

void multiply_matrices(float matrix1[3][3], float matrix2[3][3], float result[3][3]);

void multiply_matrices_with_scalar(float matrix[3][3], float scalar, float result[3][3]);

void print_matrix(float matrix[3][3]);


#endif