#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Window/window.h"

void cleanup(SDL_Window* window, SDL_GLContext glContext){
    if (glContext){
        SDL_GL_DeleteContext(glContext);
    }
    if (window){
        SDL_DestroyWindow(window);
    }
    SDL_Quit();    
}