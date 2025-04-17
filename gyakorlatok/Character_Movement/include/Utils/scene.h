#ifndef SCENE_H_
#define SCENE_H_

#include "Environment/player.h"
#include "Utils/camera.h"

#include <obj/draw.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct Scene
{
    Player player;
    Camera camera;
} Scene;

void init_scene(Scene* scene);

void update_scene(Scene* scene);

void render_scene(const Scene* scene);

/* Initializes some basic OpenGL behaviour */
void init_opengl();

void draw_origin();

void draw_player(const Model* model);

#endif /* SCENE_H_ */
