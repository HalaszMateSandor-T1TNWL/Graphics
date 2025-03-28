#ifndef SCENE_H_
#define SCENE_H_

#include "../Environment/player.h"

#include <GL/gl.h>

typedef struct Scene
{
    Player player;
    GLuint textureID;
} Scene;

void init_scene(Scene* scene);

void update_scene(Scene* scene);

void render_scene(const Scene* scene);

/* Initializes some basic OpenGL behaviour */
void init_opengl();

void draw_origin();

#endif /* SCENE_H_ */
