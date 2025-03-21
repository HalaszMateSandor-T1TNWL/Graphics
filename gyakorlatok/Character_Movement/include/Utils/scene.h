#ifndef SCENE_H_
#define SCENE_H_

typedef struct Scene
{
} Scene;

void init_scene(Scene* scene);

void update_scene(Scene* scene);

void render_scene(const Scene* scene);

void draw_origin();

#endif
