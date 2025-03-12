#ifndef CAMERA_H_
#define CAMERA_H_

#include "Utils/utils.h"
#include <stdbool.h>

typedef struct Camera{
    vec3 position;
    vec3 rotation;
    vec3 speed;
    bool is_preview_visible;
} Camera;

/* For initializing the camera with a starting position */
void initCamera(Camera* camera);

/* For updating the position of the camera */
void updateCamera(Camera* camera, double time);

/* Apply the camera settings to the view transformation */
void setView(const Camera* camera);

/* For setting the viewangle of the camera */
void rotateCamera(Camera* camera, double horizontal, double vertical);

/* For setting how fast the camera will move */
void setCameraSpeed(Camera* camera, double speed);

/* For setting how fast the camera will be able to move sideways (left or right) */
void setCameraSidesSpeed(Camera* camera, double speed);

#endif