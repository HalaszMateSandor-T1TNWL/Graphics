#include "Environment/load_texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*GLuint load_texture(char* filename)
{
    SDL_Surface* surface;
    GLuint texture_name;

    surface = IMG_Load(filename);

    glGenTextures(1, &texture_name);

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)(surface->pixels));

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return texture_name;
}*/

GLuint load_texture(char* filename){

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