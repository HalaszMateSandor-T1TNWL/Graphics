#ifndef MAIN_HELPER_H_
#define MAIN_HELPER_H_

#include "Window/camera.h"
#include "Window/scene.h"

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <stdbool.h>

#define VIEWPORT_RATIO(4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

typedef struct Helper
{
    SDL_Window* window;
    SDL_GLContext glContext;
    bool isRunning;
    double uptime;
    Camera camera;
    Scene scene;
} Helper;

void initHelper(Helper* helper, int width, int height);

void initOpenGL();

void reshape(GLsizei width, GLsizei height);

void eventHandler(Helper* helper);

void updateHelper(Helper* helper);

void destroyHelper(Helper* helper);

#endif /*MAIN_HELPER_H_*/
