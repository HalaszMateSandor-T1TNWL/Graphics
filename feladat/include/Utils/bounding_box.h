#ifndef BOUNDING_BOX_H_
#define BOUNDING_BOX_H_

#include "Utils/utils.h"
#include <stdbool.h>
#include <GL/gl.h>
#include <obj/model.h>

typedef struct Bounding_Box {

    vec3 size;
    vec3 center;
    vec3 position;
    float min_x, min_y, min_z;
    float max_x, max_y, max_z;
    
} Bounding_Box;

/* Filling up our struct so it doesn't freak out */
void init_bounding_box(Bounding_Box* box);

/* Updating the bounding box, so it always has fresh numbers to work with */
void update_player_bounding_box(Bounding_Box* box, vec3 position, vec3 size);
void update_bounding_box(Bounding_Box* box, vec3 position, vec3 size);

/* Drawing out the box for debugging reasons */
void debug_bounding_box(const Bounding_Box* box);

/* The fun part~ */
bool check_collision(Bounding_Box* player, Bounding_Box* environment);

#endif /* BOUNDING_BOX_H_ */
