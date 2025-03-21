#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "Utils/application.h"

void init_application(){
    int is_running = 0;
    int is_windowed = 1;
    double uptime;

    Camera* camera;
    SDL_Window* window;
    SDL_GLContext gl_context;

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Error, please reffer to this error code: %s", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow("Character Movement", 
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            1080, 720,
            SDL_WINDOW_OPENGL);

    if(window == NULL){
        printf("Error, please reffer to this error code: %s", SDL_GetError());
        return;
    }

    gl_context = SDL_GL_CreateContext(window);
    if(gl_context == NULL){
        printf("Error, please reffer to this error code: %s", SDL_GetError());
        return;
    }

    uptime = (double)SDL_GetTicks() / 1000;

    init_camera(camera);

    is_running = 1;
}

void event_handler(){
    while(is_running){
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                is_running = 0;
                destroy_application(window, gl_context);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    is_running = 0;
                    destroy_application(window, gl_context);
                    break;
                
                default:
                    break;
                }
            
            case SDL_MOUSEMOTION:
                

            default:
                break;
            }
        }
    } 
}