#ifndef TEXTURE_LOADER_
#define TEXTURE_LOADER_

#include <GL/gl.h>
#include <GL/glu.h>
#include <obj/model.h>

typedef struct Material {
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float shininess;
    char name[64];

} Material;

GLuint load_texture(char* filename);

void load_MTL(const char* filename, Material* materials, int* material_count);

void apply_material(const Material* mtl);

#endif