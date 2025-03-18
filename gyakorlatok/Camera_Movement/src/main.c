#include <GL/gl.h>
#include <SDL2/SDL_image.h>
#include "Window/app_window.h"

int main(int argc, char* argv[])
{
    App_window* appwindow;
    int width = 1080;
    int height = 720;

    init_window(appwindow, width, height);
    init_opengl();
    
    eventhandler(appwindow);

    destroy_window(appwindow);
}