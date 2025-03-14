#include "Window/camera.h"

#include <GL/gl.h>

#include <math.h>

void initCamera(Camera* camera){
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;

    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;

    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    camera->is_preview_visible = false;
}

void updateCamera(Camera* camera, double time){
    double angle;
    double side_angle;

    angle = degreeToRadian(camera->rotation.z);
    side_angle = degreeToRadian(camera->rotation.z + 90.0);

    
}