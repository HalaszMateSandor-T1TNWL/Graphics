#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/gl.h>

typedef GLubyte Pixel[3];

GLuint load_texture(char* filename);

#endif /*TEXTURE_H_*/