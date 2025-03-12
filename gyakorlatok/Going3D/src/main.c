#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdbool.h>

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = {0.0, 0.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat material[] = {1.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
    GLfloat material2[] = {0.0, 0.0, 1.0, 0.5};
    glMaterialfv(GL_FRONT, GL_AMBIENT, material2);

    // Draw a triangle
    glColor3ub(255,0,255);
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    glFlush();
    glFinish();
}

int main(int argc, char* argv[])
{
    SDL_Window* screen;
    SDL_Event event;

    int width = 1280;
    int height = 720;
    bool windowed = true;
    bool should_quit = false;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    screen = SDL_CreateWindow("Going 3D",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width,
                              height,
                              SDL_WINDOW_OPENGL);
    if (!screen) goto CLEANUPANDQUIT;

    SDL_GLContext glContext = SDL_GL_CreateContext(screen);
    if (!glContext) goto CLEANUPANDQUIT;

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
                        SDL_SetWindowFullscreen(screen, windowed ? SDL_FALSE : SDL_TRUE);
                    }
                    break;
            }
        }
        render();
        SDL_GL_SwapWindow(screen);
        SDL_Delay(10);
    }

CLEANUPANDQUIT:
    CleanUpAndQuit(screen, glContext);
}
