#include "../include/Utils/model_texture.h"

/*
*       Initializes a model texture by loading in the textures and storing the ID
*/
void init_modeltexture(Model_Texture* texture, const char* filename){
    
    texture->textureID = load_texture(filename);

}

/*
*       A simple get function for when we want to check the texture ID of a model
*/
void get_textureID(Model_Texture* texture){
    return texture->textureID;
}



GLuint load_texture(const char* filename){

    SDL_Surface* surface = IMG_Load(filename);
    if(!surface){
        printf("An error occoured while loading the texture: %s", IMG_GetError());
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,
         0, 
         GL_RGBA, 
         surface->w, surface->h, 
         0, 
         GL_RGBA, 
         GL_UNSIGNED_BYTE, 
         surface->pixels);

    gluBuild2DMipmaps(GL_TEXTURE_2D,
        4, 
        surface->w, surface->h,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        surface->pixels);

    SDL_FreeSurface(surface);

    return textureID;
}