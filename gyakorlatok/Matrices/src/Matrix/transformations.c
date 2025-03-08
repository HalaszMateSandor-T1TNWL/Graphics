#include "Matrix/matrix.h"
#include "Matrix/transformations.h"
#include <math.h>

void init_translation_matrix(float matrix[3][3], float dx, float dy) {
    init_identity_matrix(matrix);
    matrix[0][2] = dx;
    matrix[1][2] = dy;
}

void init_scaling_matrix(float matrix[3][3], float sx, float sy) {
    init_identity_matrix(matrix);
    matrix[0][0] = sx;
    matrix[1][1] = sy;
}

void init_rotation_matrix(float matrix[3][3], float angle) {
    init_identity_matrix(matrix);
    float radians = angle * (M_PI / 180.0f);
    matrix[0][0] = cos(radians);
    matrix[0][1] = -sin(radians);
    matrix[1][0] = sin(radians);
    matrix[1][1] = cos(radians);
}

/* -----------------Transformation Implementation-------------------- 

void translate_matrix(float matrix[3][3], float transMatrix[3][3]){
    multiply_matrices(matrix, transMatrix);
}

void scale_matrix(float matrix[3][3], float scaleMatrix[3][3]){
    multiply_matrices(matrix, scaleMatrix);
}

void rotate_matrix(float matrix[3][3], float rotationMatrix[3][3]){
    multiply_matrices(matrix, rotationMatrix);
} */