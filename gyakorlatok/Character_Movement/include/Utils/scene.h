#ifndef SCENE_H_
#define SCENE_H_

#include <GL/gl.h>

typedef struct Scene
{
} Scene;

void init_scene(Scene* scene);

void update_scene(Scene* scene);

void render_scene(const Scene* scene);

/* Initializes some basic OpenGL behaviour */
void init_opengl();

void draw_origin();

#endif SCENE_H_
