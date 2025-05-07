#include <SDL2/SDL_image.h>

#include "Window/app_window.h"

void init_window(App_window* appwindow, int width, int height)
{
    int error_code;
    int inited_loaders;

    appwindow->is_running = 0;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("%s", SDL_GetError());
        return;
    }
    
    appwindow->window = SDL_CreateWindow("Window_Test",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        width, height,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_MOUSE_GRABBED);
    
    if (appwindow->window == NULL)
    {
        printf("Unable to create a window for the application!\n");
        return;
    }
    
    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if(inited_loaders == 0)
    {
        printf("Image initialization failed: %s\n", IMG_GetError());
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
    /*SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, 0);
    SDL_WarpMouseInWindow(appwindow->window, 1080/2, 720/2); */

    appwindow->is_running = 1;
    appwindow->uptime = (double)SDL_GetTicks() / 1000;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.0, 0.6, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glLineWidth(5);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
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

    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                printf("Bye bye\n");
                appwindow->is_running = 0;
                break;
            case SDL_SCANCODE_W:
                printf("Forwards\n");
                set_camera_speed(&(appwindow->camera), 1);
                break;
            case SDL_SCANCODE_S:
                printf("Backwards\n");
                set_camera_speed(&(appwindow->camera), -1);
                break;
            case SDL_SCANCODE_D:
                printf("Right\n");
                set_camera_strafe(&(appwindow->camera), -1);
                break;
            case SDL_SCANCODE_A:
                printf("Left\n");
                set_camera_strafe(&(appwindow->camera), 1);
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                printf("Stop\n");
                set_camera_speed(&(appwindow->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                printf("Stop\n");
                set_camera_strafe(&(appwindow->camera), 0);
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            printf("A mouse button has been pressed\n");
            is_mouse_down = 1;
        case SDL_MOUSEMOTION:
            SDL_SetRelativeMouseMode(SDL_TRUE);
            //SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_CENTER, 0);
            //SDL_GetMouseState( &x, &y );
            
            x = event.motion.xrel;
            y = event.motion.yrel;

            rotate_camera(&(appwindow->camera), -x + mouse_x, -y + mouse_y);
            //using event.motion.xrel/yrel kinda works, but it's also inconsistent and choppy :/

            mouse_x = x;
            mouse_y = y;

            printf("%d :: %d\n", mouse_x, mouse_y);
            /*if(mouse_x == 0 || mouse_y == 0){
                SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_WARP_MOTION, 0);
                SDL_WarpMouseInWindow(appwindow->window, 1080/2, 720/2);
            }
            if(mouse_x == 1079 || mouse_y == 719){
                SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, 0);
                SDL_WarpMouseInWindow(appwindow->window, 1080/2, 720/2);
            }*/
            break;
        case SDL_MOUSEBUTTONUP:
            printf("A mouse button has been released\n");
            is_mouse_down = 0;
            break;
        case SDL_QUIT:
            appwindow->is_running = 0;
            break;
        default:
            break;
        }
    }
}

void render_window(App_window* appwindow)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(appwindow->camera));
    render_scene(&(appwindow->scene));
    glPopMatrix();

    SDL_GL_SwapWindow(appwindow->window);

}

void update_window(App_window* appwindow){
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - appwindow->uptime;
    appwindow->uptime = current_time;

    update_camera(&(appwindow->camera), elapsed_time);
    update_scene(&(appwindow->scene));

}

void destroy_window(App_window* appwindow)
{
    SDL_DestroyWindow(appwindow->window);
    SDL_GL_DeleteContext(appwindow->gl_context);

    SDL_Quit();
}