#include <SDL2/sdl.h>
#include <SDL2/SDL_opengl.h>

void destroy_application(SDL_Window* window, SDL_GLContext gl_context){   
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(gl_context);
}

int main(int argc, char* argv[]){
    

    destroy_application(window, gl_context);
}