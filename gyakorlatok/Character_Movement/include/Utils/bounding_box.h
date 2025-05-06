#ifndef BOUNDING_BOX_H_
#define BOUNDING_BOX_H_

#include <stdbool.h>
#include "Utils/utils.h"

typedef struct Bounding_Box {

    vec3 size;
    vec3 center;
    float min_x, min_y, min_z;
    float max_x, max_y, max_z;
    
} Bounding_Box;

/* Filling up our struct so it doesn't freak out */
void init_bounding_box(Bounding_Box* box);

/* Actually finding the coordinates of the box */
void caclculate_bounds(Bounding_Box* box);

/* Drawing out the box for debugging reasons */
void debug_bounding_box(Bounding_Box* box);

/* The fun part~ */
bool check_collision(Bounding_Box* player, Bounding_Box* environment);


#endif