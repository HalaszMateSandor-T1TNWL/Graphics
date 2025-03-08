#include "Matrix/matrix.h"
#include "Matrix/transformations.h"
#include <stdio.h>

int main(int argc, char** argv[])
{
    float a[3][3] = {
        {2.0f, 1.0f, 3.0f},
        {4.0f, 2.0f, 3.0f},
        {2.0f, 5.0f, 1.0f}
    };

    float b[3][3] = {
        {1.0f, 2.0f, 1.0f},
        {4.0f, 2.0f, 1.0f},
        {3.0f, 3.0f, 2.0f}
    };

    float tr[3][3];
    float sc[3][3];
    float rt[3][3];

    float s[3][3];
    float c[3][3];
    float I[3][3];

    init_identity_matrix(I);
    print_matrix(I);
    printf("\n");

    multiply_matrices(a, b, c);
    print_matrix(c);
    printf("\n");

    multiply_matrices_with_scalar(I, 3.0, s);
    print_matrix(s);
    printf("\n");

    init_translation_matrix(tr, 3, 2);
    init_scaling_matrix(sc, 2, 4);
    init_rotation_matrix(rt, 45);

    multiply_matrices(I, tr, s);
    print_matrix(s);
    printf("\n");

    multiply_matrices(I, sc, s);
    print_matrix(s);
    printf("\n");

    multiply_matrices(I, rt, s);
    print_matrix(s);
    printf("\n");

    return 0;
}