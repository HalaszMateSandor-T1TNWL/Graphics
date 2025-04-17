#ifndef TEXTURE_LOADER_
#define TEXTURE_LOADER_

#include <GL/gl.h>
#include "obj/model.h"

typedef GLubyte Pixel[3];

GLuint load_texture(char* filename);

#endif