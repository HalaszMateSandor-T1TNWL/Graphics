#ifndef TERRAIN_
#define TERRAIN_

#include <obj/model.h>
#include <GL/gl.h>
#include <stdlib.h>

#define SIZE 800
#define VERTEX_COUNT 128
#define COUNT VERTEX_COUNT*VERTEX_COUNT

typedef struct Terrain {

    Model* models;
    GLuint* textureID;

    int* indices;
    float* vertices;
    float* normals;
    float* texture_coords;

    float x;
    float z;

} Terrain;

void init_terrain(struct Terrain* terrain, int gridX, int gridZ);

void generate_terrain(struct Terrain* terrain);

void render_terrain(struct Terrain* terrain);

void free_terrain(struct Terrain* terrain);

#endif /* TERRAIN_ */