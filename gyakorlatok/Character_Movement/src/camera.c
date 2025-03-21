#include "../include/Utils/camera.h"

#include <SDL2/SDL.h>

void init_camera(Camera* camera){

    camera->position.x = 0.0f;
    camera->position.y = 0.0f;
    camera->position.z = 1.0f;

    camera->pitch = 20.0f;
    camera->yaw = 0.0f;
    camera->roll = 0.0f;
    camera->distance_from_player = 50.0f;
    camera->angle_around_player = 0.0f;
}

void update_camera(Camera* camera, float d_wheel, float dy, float dx){
    calculate_zoom(camera, d_wheel);
    set_pitch(camera, dy);
    calculate_angle_around_player(camera, dx);
    float horizontal_distance = calculate_horizontal(camera);
    float vertical_distance = calculate_vertical(camera);
}

void set_view(Camera* camera, float hori_distance, float verti_distance){

}


/*
*  Using the distance of the camera from the player model + angle (pitch) the camera is set in
*           We can calculate the horizontal and vertical distances using sin and cos :D
*                                   Trigonometry is BADASS
*/
float calculate_horizontal(Camera* camera){
    return (float)(camera->distance_from_player * cos(degree_to_radian(camera->pitch)));
}
float calculate_vertical(Camera* camera){
    return (float)(camera->distance_from_player * sin(degree_to_radian(camera->pitch)));
}

/* 
*   Using how much the player has moved the mouse wheel we can calculate
*                 the camera's distance from the player model
*/
void calculate_zoom(Camera* camera, float d_wheel){
    float zoom_level = d_wheel * 0.1f; // <- Multiplying it here, because it gives us a HUGE number
    camera->distance_from_player -= zoom_level; // If you want it to zoom OUT when scrolling UP change this to +=
}


/*
*    Using how much the player moved the mouse in the y direction we can
*   calculate the angle at which the camera is looking at the player model
*/
void set_pitch(Camera* camera, float dy){
    float pitch_change = dy * 0.1; // <- Once again, this gives us a HUGE number, so we're multiplying it by 0.1
    camera->pitch -= pitch_change; // If you want the camera to move UP when sliding the mouse DOWN set this to +=
}

/*
*   Using how much the player moved the mouse in the x direction we can
*     calculate the angle the camera is looking at AROUND the player
*/
void calculate_angle_around_player(Camera* camera, float dx){
    float angle_change = dx * 0.3f; // <- This doesn't give us that big of a number, but it's still uncontrolable, so we're multiplying it by 0.3
    camera->angle_around_player -= angle_change; // Changing this to += will make it go the other direction
}
