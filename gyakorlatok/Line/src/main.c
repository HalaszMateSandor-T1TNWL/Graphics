#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include "LineH/line.h"
#include "Color/color.h"

int WinMain(int argc, char** argv[]){

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    Line line;
    Color colorC;
    colorC.R = 135;
    colorC.G = 189;
    colorC.B = 100;

    int waitingForSecondClick = 0;
    int quit = 0;
    
    int WIDTH = 1280;
    int HEIGHT = 720;

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Line Maker",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH,
            HEIGHT,
            SDL_WINDOW_OPENGL
    );

    if(window == NULL) goto CLEANUP_AND_QUIT;

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if(glContext == NULL) goto CLEANUP_AND_QUIT;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(1);

    renderer = SDL_CreateRenderer(window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if(renderer == NULL) goto CLEANUP_AND_QUIT;

    while(!quit){

        while(SDL_PollEvent(&event) != 0){

            switch (event.type){

            case SDL_QUIT:
                quit = 1;
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.clicks){ 
                    case 1:
                        if (!waitingForSecondClick)
                        {
                            line.bpoint[0] = event.button.x;
                            line.bpoint[1] = event.button.y;
                            waitingForSecondClick = 1;
                        } else{
                            line.epoint[0] = event.button.x;
                            line.epoint[1] = event.button.y;
                            waitingForSecondClick = 0;

                            line.color = colorC;
                        }
                        break;
                }
                break;
            }
            glClear(GL_COLOR_BUFFER_BIT);

            if(!waitingForSecondClick){
            glColor3ub(line.color.R, line.color.G, line.color.B);
            glBegin(GL_LINES);
                glVertex2f((line.bpoint[0] / (float)WIDTH) * 2 - 1, 1 - (line.bpoint[1] / (float)HEIGHT) * 2); 
                glVertex2f((line.epoint[0] / (float)WIDTH) * 2 - 1, 1 - (line.epoint[1] / (float)HEIGHT) * 2);
            glEnd();
            }
            SDL_GL_SwapWindow(window);

            SDL_Delay(10);
            
        }

    }

    CLEANUP_AND_QUIT:
        if(glContext) SDL_GL_DeleteContext(glContext);
        if(renderer) SDL_DestroyRenderer(renderer);
        if(window) SDL_DestroyWindow(window);

        SDL_Quit();

    return 0;

}