#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdbool.h>
#include "Window/window.h"

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Event event;

    int width = 1280;
    int height = 720;
    bool windowed = true;
    bool should_quit = false;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    window = SDL_CreateWindow("Going 3D",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width,
                              height,
                              SDL_WINDOW_OPENGL);
    if (!window) goto WIPE;

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) goto WIPE;

    glEnable(GL_DEPTH_TEST);

    while (!should_quit) {
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    should_quit = true;
                    break;

                case SDL_KEYUP:
                    if (event.key.keysym.sym == SDLK_F12) {
                        windowed = !windowed;
                        SDL_SetWindowFullscreen(window, windowed ? SDL_FALSE : SDL_TRUE);
                    }
                    break;
            }
        }
        renderObject();
        update();
        SDL_GL_SwapWindow(window);
        modularFramerate();
    }

WIPE:
    glFinish();
    glFlush();
    cleanup(window, glContext);
    return 0;
}
