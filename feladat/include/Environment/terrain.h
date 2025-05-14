#ifndef TERRAIN_
#define TERRAIN_

#include <obj/model.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define SIZE 1000
#define VERTEX_COUNT 120
#define COUNT VERTEX_COUNT*VERTEX_COUNT

typedef struct Terrain {
    
    GLuint* textureID;
    SDL_Surface* heightmap_data;

    int* indices;
    float* vertices;
    float* normals;
    float* texture_coords;

    float x;
    float z;

} Terrain;

void init_terrain(struct Terrain* terrain, int gridX, int gridZ);

void load_heightmap(Terrain* terrain, const char* filename);

void generate_terrain(struct Terrain* terrain);

void render_terrain(struct Terrain* terrain);

void free_terrain(struct Terrain* terrain);

#endif /* TERRAIN_ */
