#ifndef RENDER_H_
#define RENDER_H_

void renderObject();
void modularFramerate();
void updateRotation();

#endif

#ifndef CLEANUP_H_
#define CLEANUP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

void cleanup(SDL_Window* window, SDL_GLContext glContext);

#endif