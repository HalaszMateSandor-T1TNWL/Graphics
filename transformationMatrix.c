#include <stdio.h>
#include <math.h>

int main()
{
    double x;
    double y;
    double p;
    
    double transformed[3][3];

    int transformation[] = {1,2,1};
    double matrix[][3] = { {cos(5), -sin(6), 0} , {sin(7), cos(2), 0} , {0, 0, 1}};
    double helper[3][3];

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            helper[i][j] = matrix[i][j] * transformation[i];
        }
    }
    
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 1; j++)
        {
            printf("%f %f %f\n", helper[i][j], helper[i][j+1], helper[i][j+2]);
        }
    }

    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            transformed[i][j] = helper[i][j] + helper[i+1][j+1]; 
        }
    }
    printf("\n");

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            printf("%f\n", transformed[i][j]);
        }
    }


}