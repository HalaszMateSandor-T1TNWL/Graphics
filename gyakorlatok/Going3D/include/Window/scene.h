#ifndef SCENE_H_
#define SCENE_H_

typedef struct Scene
{
} Scene;

/* Won't actually do anything, just call our Scene structure */
void initScene(Scene* scene);

/* Updates the scene by calling the structure */
void updateScene(Scene* scene);

/* Renders the scene by calling an object to draw */
void renderScene(const Scene* scene);

/* Draws the starting point of our "World" */
void drawOrigin();

#endif