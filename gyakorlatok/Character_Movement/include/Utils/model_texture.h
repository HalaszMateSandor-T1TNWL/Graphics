#ifndef MODELT_H_
#define MODELT_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct Model_Texture{

    int textureID;

}Model_Texture;

void init_modeltexture(Model_Texture* texture, const char* filename);

GLuint load_texture(const char* filename);

void get_textureID(Model_Texture* texture);

#endif