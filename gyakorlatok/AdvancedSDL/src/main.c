#include "screen/screen.h"
#include <SDL2/SDL.h>
#include <GL/gl.h>

Screen* create_screen(int width, int height)
{
    Screen* screen = malloc(sizeof(Screen));
    if(!screen){ return NULL; }

    screen->width = width;
    screen->height = height;

    screen->data = malloc(sizeof(int*) * width);
    if(!screen->data)
    {
        free(screen);
        return NULL;
    }

    for (size_t i = 0; i < width; i++)
    {
        screen->data[i] = malloc(sizeof(int*) * height);
        if(!screen->data[i]){
            for (size_t j = 0; j < i; j++)
            {
                free(screen->data[j]);
                free(screen->data);
                free(screen);
                return NULL;
            }
        }
    }

    return screen;
}

void draw_horizontal(Screen* screen, int y, int color)
{
    if (y < 0 || y >= screen->height) return;

    for (size_t x = 0; x < screen->width; x++)
    {
        screen->data[y][x] = color;
    }
}

int WinMain(int argc, char** argv[])
{
    Screen* screen = create_screen(800, 600);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    int quit = 0;

    int WIDTH = 800;
    int HEIGHT = 600;

    int windowed = 1;

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("SDL3 Window", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WIDTH, 
        HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if(window == NULL) goto CLEANUP_AND_QUIT;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL) goto CLEANUP_AND_QUIT;

    while(!quit){
        while(SDL_PollEvent(&event) != 0){
            switch(event.type){
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    WIDTH = event.window.data1;
                    HEIGHT = event.window.data2;
                    SDL_RenderPresent(renderer);
                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            quit = 1;
                            break;
                        case SDLK_F12:
                            windowed = !windowed;
                            if(windowed){
                                SDL_SetWindowFullscreen(window, SDL_FALSE);
                            } else {
                                SDL_SetWindowFullscreen(window, SDL_TRUE);
                            }
                            break;
                        case SDLK_2:
                            draw_horizontal(&screen, 100, 0xFF0000);
                            break;
                    }
                break;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderClear(renderer);

            SDL_RenderPresent(renderer);
            /* The delay is added so the OS gets time to work on other programs as well */
            /* We could've used a "Sleep" here as well */
            SDL_Delay(10);
        }
    }
    
    /* We're using a GOTO statement to make sure 
        all memory cells are freed upon a failure */

        CLEANUP_AND_QUIT:
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();

    return 0;
}