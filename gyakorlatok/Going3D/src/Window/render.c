#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "Window/window.h"

/* global variable for the pyramid's rotation angle */
float triRotationAngle = 0;

/* global variable for the texture's texture ID */
GLuint textureID;

/* Now comes the fun part~ */
GLuint LoadTexture(const char* filename){

    SDL_Surface* surface = IMG_Load(filename);
    if(!surface){
        printf("An error occoured while loading the texture: %s\n ", IMG_GetError());
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       //basically clamps the texture to your rendered model's edge
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       //same as the previous one, just this time not with the S coordinates, but rather T
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //for when LOD decides the image should be MINIFIED it sets the algorithm to liniear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //same as the previous one, just this time for MAGNIFICATION


    glTexImage2D(GL_TEXTURE_2D,     //specifies the target texture aka. the image you're loading in
                0,                  //specifies the level of detail you'll be loading the image in in (in?)
                GL_RGBA,            //specifies the color components in the image (A stands for Alpha transparency, here)
                surface->w,         //The width and
                surface->h,         //height of the image provided
                0,                  //it just HAS to be 0 (says so in the documentation, don't argue with me D:<)
                GL_RGBA,            //specifies the format of the pixel data
                GL_UNSIGNED_BYTE,   //specifies the data TYPE of the pixel data
                surface->pixels);   //specifies the image pointer 

    gluBuild2DMipmaps(GL_TEXTURE_2D,        //specifies the target texture (has to be GL_TEXTURE_2D for obvious reasons)
                        4,                  //the internal storage format of the texture image (let that mean, whatever it means, it just has to be 1, 2, 3 or 4)
                        surface->w,         //the width and
                        surface->h,         //height of the texture
                        GL_RGBA,            //and everything else from
                        GL_UNSIGNED_BYTE,   //here is the same as the
                        surface->pixels);   //previous one  

    SDL_FreeSurface(surface);

    return textureID;
}

void initTexture(){
    textureID = LoadTexture("../textures/Hoofs.png");
}

void renderObject() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    initTexture();

    glBindTexture(GL_TEXTURE_2D, textureID);

    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = {1.0, 1.0, 0.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat material[] = {0.0, 0.0, 1.0, 0.5};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
    GLfloat material2[] = {1.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, material2);
    
    //Face Culling for performance
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Draw a triangle
    glRotatef(triRotationAngle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);

    // Front face
    glTexCoord2f(0.5f, -1.0f); glVertex3f(0.0f, 1.0f, 0.0f); // Top
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // Bottom right

    // Right face
    glTexCoord2f(0.5f, -1.0f); glVertex3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

    // Back face
    glTexCoord2f(0.5f, -1.0f); glVertex3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left face
    glTexCoord2f(0.5f, -1.0f); glVertex3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

    // Base (two triangles)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);

    glEnd();
}

void updateRotation()
{
    triRotationAngle += 1;
    if(triRotationAngle > 360) {triRotationAngle -= 360; }
}

void modularFramerate()
{
    Uint32 frameStart = SDL_GetTicks();
    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if(frameTime < 16){
        SDL_Delay(16 - frameTime);
    }
}

void cleanup(SDL_Window* window, SDL_GLContext glContext){
    if (glContext){
        SDL_GL_DeleteContext(glContext);
    }
    if (window){
        SDL_DestroyWindow(window);
    }
    glDeleteTextures(1, &textureID);
    SDL_Quit();
}