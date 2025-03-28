#ifndef UTILS_H_
#define UTILS_H_

#include <math.h>

/* Supposed to emulate the vec3 from GLSL */
typedef struct vec3 {
    float x;
    float y;
    float z;
} vec3;

/* Color structure for better readability */
typedef struct Color {
    unsigned char R;
    unsigned char G;
    unsigned char B;
} Color;

typedef struct Material {
    struct Color ambient;
    struct Color diffuse;
    struct Color specular;
} Material;

/* A function for turning degrees into radians for usage with sin() and cos() */
double degree_to_radian(double degree);

#endif