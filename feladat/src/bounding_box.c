#include "Utils/bounding_box.h"
#include <stdio.h>

void init_bounding_box(Bounding_Box* box){
    box->center.x = box->center.y = box->center.z = 0;
    box->size.x = box->size.y = box->size.z = 0;

    box->min_x = box->min_y = box->min_z = INFINITY;
    box->max_x = box->max_y = box->max_z = -INFINITY;

    box->position.x = 0.0f;
    box->position.y = 0.0f;
    box->position.z = 0.0f;
}

void debug_bounding_box(const Bounding_Box* box) {
    
    GLfloat vertices[] = {
        box->min_x,      box->min_y,     box->min_z,
        box->max_x,      box->min_y,     box->min_z,
        box->max_x,      box->max_y,     box->min_z,
        box->min_x,      box->max_y,     box->min_z,
        box->min_x,      box->min_y,     box->max_z,
        box->max_x,      box->min_y,     box->max_z,
        box->max_x,      box->max_y,     box->max_z,
        box->min_x,      box->max_y,     box->max_z
    };

    GLuint indices[] = {
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 5, 5, 6, 6, 7, 7, 4,
        0, 4, 1, 5, 2, 6, 3, 7
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void update_player_bounding_box(Bounding_Box* box, vec3 position, vec3 size) {
    box->center.x = (box->max_x + box->min_x) / 2;
    box->center.y = (box->max_y + box->min_y) / 2;
    box->center.z = (box->max_z + box->min_z) / 2;

    box->size.x = size.x;
    box->size.y = size.y;
    box->size.z = size.z;

    box->max_x = position.x + box->size.x;
    box->min_x = position.x - box->size.x;

    box->min_y = position.y - box->size.y;
    box->max_y = position.y + box->size.y;
    
    box->min_z = position.z - box->size.z;
    box->max_z = position.z + box->size.z;

    printf("X: (%f, %f)\nY: (%f, %f)\nZ: (%f, %f)\n",
           box->min_x, box->max_x, box->min_y, box->max_y, box->min_z, box->max_z);
}

void update_bounding_box(Bounding_Box* box, vec3 offset, float speedFPS) {
	box->min_x += offset.x * speedFPS;
	box->max_x += offset.x * speedFPS;
	box->min_y += offset.y;
	box->max_y += offset.y;
	box->min_z += offset.z * speedFPS;
	box->max_z += offset.z * speedFPS;
	
	box->position.x += offset.x * speedFPS;
	box->position.y += offset.y * speedFPS;
	box->position.z += offset.z * speedFPS;
	
	printf("X: (%f, %f)\nY: (%f, %f)\nZ: (%f, %f)\n",
           box->min_x, box->max_x, box->min_y, box->max_y, box->min_z, box->max_z);
}

bool check_collision(Bounding_Box* player, Bounding_Box* environment) {
    bool overlap_x = player->max_x >= environment->min_x && player->min_x <= environment->max_x;

    bool overlap_y = player->max_y >= environment->min_y && player->min_y <= environment->max_y;

    bool overlap_z = player->max_z >= environment->min_z && player->min_z <= environment->max_z;

    return overlap_x && overlap_y && overlap_z;
}
