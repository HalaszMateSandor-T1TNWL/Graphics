#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Utils/utils.h"

typedef struct Camera {

    vec3 position;
    float distance_from_player;
    float angle_around_player;
    float pitch;
    float yaw;
    float roll;
    
} Camera;

/* For initializing the camera with a starting position */
void init_camera(Camera* camera);

/* For updating the position of the camera */
void update_camera(Camera* camera, float d_wheel, float dy, float dx);

/* Calculates the horizontal distance from player model */
float calculate_horizontal(Camera* camera);

/* Calculates the vertical distance from the player model */
float calculate_vertical(Camera* camera);

/* Calculates how far the camera actually is from the player */
void calculate_zoom(Camera* camera, float d_wheel);

/* Calculates the current degree the camera is at while looking at the player model */
void set_pitch(Camera* camera, float dy);

/* Calculates the angle from which the camera is looking at the player model */
void calculate_angle_around_player(Camera* camera, float dx);

/* Apply the camera settings to the view transformation */
void set_view(Camera* camera, float hori_distance, float verti_distance);

#endif