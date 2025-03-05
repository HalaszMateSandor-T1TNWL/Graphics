#include <GL/gl.h>
#include <GL/glu.h>
#include <Gl/glext.h>

void Display(void)
{
    /* Clear all pixels */

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    
    glBegin(GL_POLYGON);
        glVertex3f(0.25, 0.25, 0.25);
        glVertex3f(0.75, 0.25, 0.0);
        glVertex3f(0.75, 0.75, 0.0);
        glVertex3f(0.25, 0.75, 0.0);
    glEnd();

    /* DON'T WAIT!!
       START PROCESSING BUFFERED OPENGL ROUTINES! 
    */

    glFlush();
}

void Init(void)
{
    /* Select clearing colors */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* Initialize viewing values */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

/* Declare initial window size, position, and display mode
   (single buffer and RGBA). Open window with "Hello"
   in its title bar. Call initialization routines. 
   Enter main loop and process events.
*/

int main(int argc, char** argv)
{
    


    return 0;
}