#include "Utils/bounding_box.h"

void init_bounding_box(Bounding_Box* box){
    box->center.x = box->center.y = box->center.z = 0;
    box->size.x = box->size.y = box->size.z = 0;

    box->min_x = box->min_y = box->min_z = 0;
    box->max_x = box->max_y = box->max_z = 0;
}
