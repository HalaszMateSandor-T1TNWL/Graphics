#include "Environment/load_texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

GLuint load_texture(char* filename) {
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        printf("Failed to load texture: %s\n", IMG_GetError());
        return 0;
    }

    GLuint texture_name;
    glGenTextures(1, &texture_name);
    glBindTexture(GL_TEXTURE_2D, texture_name);

    GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);

    return texture_name;
}

void load_MTL(const char* filename, Material* materials, int* material_count) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    Material* current = NULL;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "newmtl ", 7) == 0) {
            current = &materials[(*material_count)++];
            sscanf(line + 7, "%s", current->name);
            current->ambient[3] = current->diffuse[3] = current->specular[3] = 1.0f;
        } else if (current && strncmp(line, "Ka ", 3) == 0) {
            sscanf(line + 3, "%f %f %f", &current->ambient[0], &current->ambient[1], &current->ambient[2]);
        } else if (current && strncmp(line, "Kd ", 3) == 0) {
            sscanf(line + 3, "%f %f %f", &current->diffuse[0], &current->diffuse[1], &current->diffuse[2]);
        } else if (current && strncmp(line, "Ks ", 3) == 0) {
            sscanf(line + 3, "%f %f %f", &current->specular[0], &current->specular[1], &current->specular[2]);
        } else if (current && strncmp(line, "Ns ", 3) == 0) {
            sscanf(line + 3, "%f", &current->shininess);
        }
    }

    fclose(file);
}

void apply_material(const Material* mtl) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mtl->ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mtl->diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mtl->specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mtl->shininess);
}

#if 0 /* This one doesn't work anymore for what I'm doing */
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
#endif