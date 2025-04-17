#include "../include/Utils/scene.h"

/*
*       These two do basically nothing, but set the values to zero or smth, idk
*/
void init_scene(Scene* scene) {
    init_player(&scene->player); 
}

void update_scene(Scene* scene) {

}

/*
*           A function for rendering everything necessary to the world
*/
void render_scene(const Scene* scene) {
    draw_origin();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glScalef(0.05f, 0.05f, 0.05f);
        glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
        glTranslatef(scene->player.position.x, scene->player.position.y, scene->player.position.z);
        glRotatef(scene->player.rotation.y, 0.0f, scene->player.rotation.y, 0.0f);
        draw_player(&scene->player.player_model);
    glPopMatrix();
}

/*
*                  Basic OpenGL settings compacted into one function
*/
void init_opengl() {

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.0f, 0.5f, 0.2f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);

    glBegin(GL_TRIANGLES);

        glColor3f(1, 0, 0);
        glVertex2f(0, 0);
        glColor3f(0, 1, 0);
        glVertex2f(1, 0);
        glColor3f(0, 0, 1);
        glVertex2f(0, 1);
        
    glEnd();

}

/*
*                   Placeholder, just so I can see something on the screen
*/
void draw_origin() {
    glBegin(GL_LINES);

        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);

        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);

        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1);

    glEnd();
}

void draw_player(const Model* model) {
    int i, k;
    int vertex_index, texture_index, normal_index;
    float x, y, z, u, v;

    glBegin(GL_TRIANGLES);

    for (i = 0; i < model->n_triangles; ++i) {
        for (k = 0; k < 3; ++k) {

            normal_index = model->triangles[i].points[k].normal_index;
            x = model->normals[normal_index].x;
            y = model->normals[normal_index].y;
            z = model->normals[normal_index].z;
            glNormal3f(x, y, z);

            texture_index = model->triangles[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            glTexCoord2f(u, 1.0 - v);

            vertex_index = model->triangles[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3f(x, y, z);
        }
    }

    glEnd();
}
