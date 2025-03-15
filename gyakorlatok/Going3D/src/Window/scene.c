#include "Window/scene.h"

#include <GL/gl.h>

void initScene(Scene* scene){}

void updateScene(Scene* scene){}

void renderScene(const Scene* scene)
{
    drawOrigin();
}

void drawOrigin(){
    glBegin(GL_LINES)

    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);
    
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);

    glEnd();
}