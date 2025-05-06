#ifndef SCENE_H_
#define SCENE_H_

#include "Environment/entity.h"
#include "Utils/camera.h"
#include "Environment/terrain.h"

#include <obj/draw.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

enum {
    SKY_LEFT = 0,
    SKY_BACK,
    SKY_RIGHT,
    SKY_FRONT,
    SKY_TOP,
    SKY_BOTTOM
};

typedef struct Scene {

    Entity player;
    Entity* objects;
    Camera camera;
    Terrain terrain;
    GLuint skybox[6];

} Scene;

void init_scene(Scene* scene);

void update_scene(Scene* scene);

void render_scene(Scene* scene);

void terrain_renderer(Scene* scene);

/* Initializes some basic OpenGL behaviour */
void init_opengl();

void init_skybox(Scene* scene);

void draw_skybox(Scene* scene, float size);

void free_skybox(Scene* scene);

void draw_player(const Model* model);

void draw_bounding_box(const Entity* entity);

#endif /* SCENE_H_ */
