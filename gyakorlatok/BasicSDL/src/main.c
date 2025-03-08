#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int WinMain(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error, SDL failed to initialize.\nSDL Error: '%s'",SDL_GetError());
        return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0); 
    if(!window){
        printf("Error: failed to open window\nSDL Error:'%s'", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Error: Failed to create renderer\nSLD Error: '%s'", SDL_GetError());
        return 1;
    }
    
    bool running = true;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                running = false;
                break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255,255,255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

    return 0;
}