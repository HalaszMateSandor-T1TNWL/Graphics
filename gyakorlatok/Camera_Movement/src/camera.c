#include "Utils/camera.h"
#include "Utils/utils.h"
#include <math.h>
#include <GL/gl.h>

/* Initializes the camera's starting position, rotation and speed */
void init_camera(Camera* camera){

    camera->position.x = 0.0f;
    camera->position.y = 0.0f;
    camera->position.z = 2.0f;

    camera->rotation.x = 0.0f;
    camera->rotation.y = 0.0f;
    camera->rotation.z = 0.0f;

    camera->speed.x = 0.0f;
    camera->speed.y = 0.0f;
    camera->speed.z = 0.0f;

}


/* Updates the camera's facing direction */
void update_camera(Camera* camera, double time){

    double angle;
    double strafe_angle;

    angle = degreeToRadian(camera->rotation.z);
    strafe_angle = degreeToRadian(camera->rotation.z + 90.0);

    camera->rotation.x = cos(angle) * camera->speed.y * time; 
    camera->rotation.y = sin(angle) * camera->speed.y * time; 

    camera->rotation.x = cos(strafe_angle) * camera->speed.x * time;
    camera->rotation.y = sin(strafe_angle) * camera->speed.x * time;
}

/* Sets which way the camera's currently looking */
void set_view(const Camera* camera){

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0.0, 0.0);
    glRotatef(-(camera->rotation.z + 90), 0.0, 0.0, 1.0);

    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);

}

/* Enables rotation both horizontally and vertically */
void rotate_camera(Camera* camera, double horizontal, double vertical){

    camera->rotation.z += horizontal;
    camera->rotation.z += vertical;

    if(camera->rotation.z > 360.0){
        camera->rotation.z -= 360.0;
    }

    if(camera->rotation.z < 0.0){
        camera->rotation.z += 360.0;
    }

    if(camera->rotation.x > 360.0){
        camera->rotation.x -= 360.0;
    }

    if(camera->rotation.x < 0.0){
        camera->rotation.x += 360.0;
    }
}

/* "Moves" the camera on the Y axis (forwards or backwards) */
void set_camera_speed(Camera* camera, double speed){
    camera->speed.y = speed;
}

/* "Moves" the camera on the X axis (left or right) */
void set_camera_strafe(Camera* camera, double speed){
    camera->speed.x = speed;
}