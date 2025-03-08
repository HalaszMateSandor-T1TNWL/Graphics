#include "Matrix/matrix.h"
#include <stdio.h>

void init_null_matrix(float matrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[i][j] = 0.0;
        }
    } 
}

void init_identity_matrix(float matrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(i == j)
            {
                matrix[i][j] = 1.0;
            }
            else
            {
                matrix[i][j] = 0.0;              
            }
        }
    }
}

void multiply_matrices_with_scalar(float matrix[3][3], float scalar, float result[3][3]){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
}

void multiply_matrices(float matrix1[3][3], float matrix2[3][3], float result[3][3]){
    float helper[3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = 0.0;
            for (int k = 0; k < 3; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void print_matrix(float matrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}