#ifndef CAMERA_H_
#define CAMERA_H_

#include "Utils/utils.h"
#include <stdbool.h>

typedef struct Camera{

    vec3 position;
    vec3 rotation;
    vec3 speed;
    
} Camera;

/* For initializing the camera with a starting position */
void init_camera(Camera* camera);

/* For updating the position of the camera */
void update_camera(Camera* camera, double time);

/* Apply the camera settings to the view transformation */
void set_view(const Camera* camera);

/* For setting the viewangle of the camera */
void rotate_camera(Camera* camera, double horizontal, double vertical);

/* For setting how fast the camera will move */
void set_camera_speed(Camera* camera, double speed);

/* For setting how fast the camera will be able to move sideways (left or right) */
void set_camera_strafe(Camera* camera, double speed);

#endif