#ifndef APP_H_
#define APP_H_

#include "camera.h"
#include "scene.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdbool.h>
#include <stdio.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

typedef struct App
{
    SDL_Window* window;
    SDL_GLContext gl_context;

    int is_running;
    bool is_windowed;
    double uptime;

    Camera camera;
    Scene scene;
} App;

/* Initalizes everything needed for an App structure */
void init_application(App* app);

/* Handles the running of the window and the events happening inside it */
void event_handler(App* app);

/* A wrapper function for move(), so I can call it in main seperately */
void movement(App* app);

/* Gives back time in miliseconds */
double get_current_time(App* app);

/* Makes it so we have enough time between frame renders */
void modular_framerate(App* app);

/* Updates information regarding the application */
void update_application(App* app);

/* Handles graphical rendering */
void render_application(App* app);

/* Gives us the basic rendering pipeline */
void shape_window(GLsizei width, GLsizei height);

/* Frees up memory used by application */
void destroy_application(App* app);

#endif /* APP_H_ */