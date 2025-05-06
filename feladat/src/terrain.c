#include "Environment/terrain.h"
#include "Environment/load_texture.h"

void init_terrain(struct Terrain* terrain, int gridX, int gridZ) {
    terrain->textureID = malloc(sizeof(GLuint) * 2);
    if (!terrain->textureID) {
        fprintf(stderr, "Failed to allocate memory for textureID\n");
        exit(EXIT_FAILURE);
    }

    terrain -> indices = malloc(sizeof(int)*6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1));
    terrain -> vertices = malloc(sizeof(float)*COUNT*3);
    terrain -> normals = malloc(sizeof(float)*COUNT*3);
    terrain -> texture_coords = malloc(sizeof(float)*COUNT*2);

    terrain -> x = gridX * SIZE;
    terrain -> z = gridZ * SIZE;
}

void generate_terrain(struct Terrain* terrain) {
    
    int vertex_pointer = 0;
    for (int i = 0; i < VERTEX_COUNT; i++) {
        for (int j = 0; j < VERTEX_COUNT; j++) {
            terrain -> vertices[vertex_pointer*3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
            terrain -> vertices[vertex_pointer*3+1] = 0.0f;
            terrain -> vertices[vertex_pointer*3+2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;

            terrain -> normals[vertex_pointer*3] = 0;
            terrain -> normals[vertex_pointer*3+1] = 1;
            terrain -> normals[vertex_pointer*3+2] = 0;

            terrain -> texture_coords[vertex_pointer*2]   = (float)j / ((float)VERTEX_COUNT - 1);
            terrain -> texture_coords[vertex_pointer*2+1] = (float)i / ((float)VERTEX_COUNT - 1);

            vertex_pointer++;
        }
    }

    int pointer = 0;
    for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
        for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
            int top_left = (gz * VERTEX_COUNT) + gx;
            int top_right = top_left + 1;

            int bottom_left = ((gz + 1) * VERTEX_COUNT) + gx;
            int bottom_right = bottom_left + 1;

            terrain -> indices[pointer++] = top_left;
            terrain -> indices[pointer++] = bottom_left;
            terrain -> indices[pointer++] = top_right;

            terrain -> indices[pointer++] = top_right;
            terrain -> indices[pointer++] = bottom_left;
            terrain -> indices[pointer++] = bottom_right;
        }
    }
}

void render_terrain(struct Terrain* terrain) {
    int index_count = 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1);

    generate_terrain(terrain);

    for (int i = 0; i < index_count; i += 3)
    {
        int index0 = terrain -> indices[i];
        int index1 = terrain -> indices[i + 1];
        int index2 = terrain -> indices[i + 2];

        glBegin(GL_TRIANGLES);

            glNormal3f(terrain->normals[index0*3], terrain->normals[index0*3+1], terrain->normals[index0*3+2]);
            glTexCoord2f(terrain->texture_coords[index0*2], terrain->texture_coords[index0*2+1]);
            glVertex3f(terrain->vertices[index0*3], terrain->vertices[index0*3+1], terrain->vertices[index0*3+2]);

            glNormal3f(terrain->normals[index1*3], terrain->normals[index1*3+1], terrain->normals[index1*3+2]);
            glTexCoord2f(terrain->texture_coords[index1*2], terrain->texture_coords[index1*2+1]);
            glVertex3f(terrain->vertices[index1*3], terrain->vertices[index1*3+1], terrain->vertices[index1*3+2]);

            glNormal3f(terrain->normals[index2*3], terrain->normals[index2*3+1], terrain->normals[index2*3+2]);
            glTexCoord2f(terrain->texture_coords[index2*2], terrain->texture_coords[index2*2+1]);
            glVertex3f(terrain->vertices[index2*3], terrain->vertices[index2*3+1], terrain->vertices[index2*3+2]);

        glEnd();
    }
}

void free_terrain(struct Terrain* terrain) {
    free(terrain->indices);
    free(terrain->vertices);
    free(terrain->normals);
    free(terrain->texture_coords);
    glDeleteTextures(1, terrain->textureID);
    free(terrain->textureID);

    init_terrain(terrain, 0, 0);
}