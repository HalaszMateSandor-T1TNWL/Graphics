#include <GL/gl.h>
#include <SDL2/SDL_image.h>
#include "Window/app_window.h"

int main(int argc, char* argv[])
{
    App_window appwindow;
    int width = 1080;
    int height = 720;

    init_window(&appwindow, width, height);
    
    while(appwindow.is_running)
    {
        render_window(&appwindow);
        eventhandler(&appwindow);
        update_window(&appwindow);

    }
    destroy_window(&appwindow);

    return 0;
}