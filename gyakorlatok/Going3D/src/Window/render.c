#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "Window/window.h"

float angle = 0.0f;

void renderObject() {

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    // Enable lighting
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    GLfloat light_position[] = {0.0, 0.0, 1.0, 1.0};
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat material[] = {1.0, 0.0, 0.0, 1.0};
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
    GLfloat material2[] = {0.0, 0.0, 1.0, 0.5};
    //glMaterialfv(GL_FRONT, GL_AMBIENT, material2);

    // Draw a triangle
    glRotatef(angle, 0.0f, 0.5f, 0.0f);

    glTexParameteri()

    glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0); glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0, 1, 0); glVertex3f(-1.0f, -1.0f, 1.0f);
        glColor3f(0, 0, 1); glVertex3f(1.0f, -1.0f, 1.0f);

        glColor3f(1, 0, 0); glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0, 1, 0); glVertex3f(-1.0f, -1.0f, 1.0f);
        glColor3f(0, 0, 1); glVertex3f(0.0f, -1.0f, -1.0f);

        glColor3f(1, 0, 0); glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0, 1, 0); glVertex3f(0.0f, -1.0f, -1.0f);
        glColor3f(0, 0, 1); glVertex3f(1.0f, -1.0f, 1.0f);
        
        glColor3f( 1, 0, 0 ); glVertex3f( -1.0f, -1.0f, 1.0f);
        glColor3f( 0, 1, 0 ); glVertex3f( 0.0f, -1.0f, -1.0f);
        glColor3f( 0, 0, 1 ); glVertex3f( 1.0f, -1.0f, 1.0f);
    glEnd();
}

void update()
{
    angle += 1;
    if(angle > 360) angle -= 360;
}

void modularFramerate()
{
    Uint32 frameStart = SDL_GetTicks();
    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if(frameTime < 16){
        SDL_Delay(16 - frameTime);
    }
}