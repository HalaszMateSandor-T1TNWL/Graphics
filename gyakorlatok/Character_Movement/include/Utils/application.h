#ifndef APP_H_
#define APP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>

#include "../Utils/camera.h"
#include "../Utils/scene.h"
#include "../Environment/player.h"

typedef struct App
{
    SDL_Window* window;
    SDL_GLContext gl_context;

    int is_running;
    bool is_windowed;
    double uptime;

    Camera camera;
    Scene scene;
    Player player;
} App;

/* Initalizes everything needed for an App structure */
void init_application(App* app);

/* Gives back time in miliseconds */
double get_current_time(App* app);

/* Updates information regarding the application */
void update_application(App* app);

/* Handles the running of the window and the events happening inside it */
void event_handler(App* app);

/* Frees up memory used by application */
void destroy_application(App* app);


#endif