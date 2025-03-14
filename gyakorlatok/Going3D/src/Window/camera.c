#include "Window/camera.h"

#include <GL/gl.h>

#include <math.h>

void initCamera(Camera *camera)
{
    camera->position.x = 0.0;
    camera->poistion.y = 0.0;
    camera->position.z = 1.0;

    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;

    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    camera->is_preview_visible = false;
}

void updateCamera(Camera *camera, double time)
{
    double angle;
    double side_angle;

    angle = degreeToRadian(camera->rotation.z);
    side_angle = degreeToRadian(camera->rotation.z + 90.0);

    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;

    camera->rotation.x += cos(side_angle) * camera->speed.x * time;
    camera->rotation.y += sin(side_angle) * camera->speed.x * time;
}

void setView(const Camera* camera){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);

    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotateCamera(Camera* camera, double horizontal, double vertical){
    camera->rotation.z += horizontal;
    camera->rotation.z += vertical;

    if(camera->rotation.z < 0){
        camera->rotation.z += 360.0;
    }
    if(camera->rotation.z > 360){
        camera->rotation.z -= 360;
    }
    if(camera->rotation.x < 0){
        camera->rotation.x += 360;
    }
    if(camera->rotation.x > 360){
        camera->rotation.x -=360;
    }
}

void setCameraSpeed(Camera* camera, double speed){
    camera->speed.y = speed;
}

void setCameraSidesSpeed(Camera* camera, double speed){
    camera->speed.x = speed;
}
