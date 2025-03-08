#ifndef TRANS_H_INIT_
#define TRANS_H_INIT_

void init_translation_matrix(float matrix[3][3], float dx, float dy);
void init_scaling_matrix(float matrix[3][3], float sx, float sy);
void init_rotation_matrix(float matrix[3][3], float angle);

#endif

#ifndef TRANS_H_IMPL
#define TRANS_H_IMPL

void translate_matrix(float matrix[3][3], float transMatrix[3][3]);
void scale_matrix(float matrix[3][3], float scaleMatrix[3][3]);
void rotate_matrix(float matrix[3][3], float rotationMatrix[3][3]);

#endif