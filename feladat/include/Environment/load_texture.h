#ifndef TEXTURE_LOADER_
#define TEXTURE_LOADER_

#include <GL/gl.h>
#include <GL/glu.h>
#include <obj/model.h>
#include <stdio.h>

typedef struct Material {
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float shininess;
    char name[64];

} Material;

/* Loads in a picture (usually PNG) and turns it into something OpenGl can use for texturing
*      (returns an unsigned integer with the ID of the texture that was loaded in)
*/
GLuint load_texture(char* filename);

#endif
