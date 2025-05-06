#ifndef UTILS_H_
#define UTILS_H_

#include <math.h>

/* Supposed to emulate the vec3 from GLSL */
typedef struct vec3 {
    float x;
    float y;
    float z;
} vec3;

/* A function for turning degrees into radians for usage with sin() and cos() */
double degree_to_radian(double degree);

#endif