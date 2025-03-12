#include <SDL2/SDL.h>
#include <GL/gl.h>

void CleanUpAndQuit(SDL_Window* window, SDL_GLContext glContext){
    if (glContext)
        SDL_GL_DeleteContext(glContext);
        glClear(GL_COLOR_BUFFER_BIT);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}