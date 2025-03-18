#include <SDL2/SDL.h>
#include <GL/gl.h>
#include "Window/app_window.h"

void init_window(App_window* appwindow, int width, int height)
{

    int error_code;
    int inited_loaders;

    error_code = SDL_Init(SDL_INIT_VIDEO);
    if (error_code != 0)
    {
        printf("%s", SDL_GetError());
        return;
    }
    
    appwindow->window = SDL_CreateWindow("Window_Test",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        width, height,
                                        SDL_WINDOW_OPENGL);
    if (appwindow->window == NULL)
    {
        printf("Unable to create a window for the application!\n");
        return;
    }
    

    appwindow->gl_context = SDL_GL_CreateContext(appwindow->window);
    if (appwindow->gl_context == NULL)
    {
        printf("Unable to create a proper link with OpenGL!\n");
        return;
    }
    
    init_opengl();
    reshape(width, height);

    init_camera(&(appwindow->camera));
    init_scene(&(appwindow->scene));

    appwindow->is_running = 1;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 0.1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, z, w, h;
    double ratio;

    ratio = (double)width / height;
    if(ratio > VIEWPORT_RATIO){
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    } else{
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 10
    );
}

void eventhandler(App_window* appwindow)
{
    SDL_Event event;

    static int is_mouse_down = 0;
    static int mouse_x = 0;
    static int mouse_y = 0;

    int x;
    int y;

    while (appwindow->is_running == 1)
    {
        while(SDL_PollEvent(&event)){

            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                    appwindow->is_running = 0;
                    break;
                case SDL_SCANCODE_W:
                    set_camera_speed(&(appwindow->camera), 1);
                    printf("Forwards\n");
                    break;
                case SDL_SCANCODE_S:
                    set_camera_speed(&(appwindow->camera), -1);
                    printf("Backwards\n");
                    break;
                case SDL_SCANCODE_A:
                    set_camera_strafe(&(appwindow->camera), 1);
                    printf("Left\n");
                    break;
                case SDL_SCANCODE_D:
                    set_camera_strafe(&(appwindow->camera), -1);
                    printf("Right\n");
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                printf("%d\n", event.motion.x);
                printf("%d\n", event.motion.y);
            }
        }
    }
}

void destroy_window(App_window* appwindow)
{
    SDL_DestroyWindow(appwindow->window);
    SDL_GL_DeleteContext(appwindow->gl_context);
}