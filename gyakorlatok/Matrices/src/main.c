#include "Matrix/matrix.h"
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

    return 0;
}