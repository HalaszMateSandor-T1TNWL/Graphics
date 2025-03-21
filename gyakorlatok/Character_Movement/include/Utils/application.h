#ifndef APP_H_
#define APP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Utils/camera.h"

typedef struct App
{
    SDL_Window* window;
    SDL_GLContext gl_context;
    int is_running;
    int is_windowed;
    double uptime;
    Camera* camera;
    Scene scene;
} App;

/* Initalizes everything needed for an App structure */
void init_application();




#endif