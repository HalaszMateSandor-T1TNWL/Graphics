#ifndef SCENE_H_
#define SCENE_H_

#include "Environment/entity.h"
#include "Utils/camera.h"
#include "Environment/terrain.h"

#include <obj/draw.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#define MAX_OBJECTS 30

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

    vec3 light_pos;
    GLfloat brightness;
    bool is_fog;

} Scene;

/* Sets everything up with default values, so C don't freak out */
void init_scene(Scene* scene);

/* Updates certain aspects about the scene:
*   Brightness,
*   Light position,
*   Is fog shown
*/
void update_scene(Scene* scene, float speedFPS);

/* Reads in user input and changes certain aspects about the scene */
void change_scene_settings(Scene* scene);

void render_scene(Scene* scene);

/* Renders the procedually generated terrain */
void terrain_renderer(Scene* scene);

/* Initializes some basic OpenGL behaviour */
void init_opengl();

/* Sets the skybox up with starter values */
void init_skybox(Scene* scene);

/* Draws the skybox with primitives and applies textures to them */
void draw_skybox(Scene* scene, float size);

/* Frees the allocated space for the skybox by deleting all stored textures */
void free_skybox(Scene* scene);

#endif /* SCENE_H_ */
