#ifndef APP_WINDOW_H_
#define APP_WINDOW_H_

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include "Utils/camera.h"
#include "Utils/scene.h"

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

typedef struct App_window
{
    SDL_Window* window;
    SDL_GLContext gl_context;

    int is_running;
    double uptime;

    Camera camera;
    Scene scene;

} App_window;

/* Initializes our blank window */
void init_window(App_window* appwindow, int width, int height);

/* Initializes everything we are going to need from OpenGL */
void init_opengl();

/* Allows us to resize/reshape our window */
void reshape(GLsizei width, GLsizei height);

/* Will handle everything the user does inside the window */
void eventhandler(App_window* appwindow);

/* Refreshes the state of the window */
void update_window(App_window* appwindow);

/* Will handle the destruction of our window with all of its components, freeing up memory */
void destroy_window(App_window* appwindow);

#endif