#ifndef SCENE_H_
#define SCENE_H_

#include "Environment/player.h"
#include "Utils/camera.h"
#include "Environment/terrain.h"

#include <obj/draw.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct Scene {

    Player player;
    Camera camera;
    Terrain terrain;

} Scene;

void init_scene(Scene* scene);

void update_scene(Scene* scene);

void render_scene(Scene* scene);

void terrain_renderer(Scene* scene);

/* Initializes some basic OpenGL behaviour */
void init_opengl();

void draw_player(const Model* model);

#endif /* SCENE_H_ */
