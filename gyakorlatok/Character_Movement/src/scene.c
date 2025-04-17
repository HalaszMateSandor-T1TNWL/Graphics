#include "Utils/scene.h"

/*
*       Initializes the components necessary to the scene
*/
void init_scene(Scene* scene) {
    init_player(&scene->player);
    scene->player.textureID = load_texture("../textures/body.png");
    init_camera(&scene->camera);
}

void update_scene(Scene* scene)
{
}

/*
*           A function for rendering everything necessary to the world
*/
void render_scene(const Scene* scene) {
    glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
        gluLookAt(
            0.0f, 5.0f, 10.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        );

        glBindTexture(GL_TEXTURE_2D, scene->player.textureID);
        glEnable(GL_TEXTURE_2D);

        // Enable lighting
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        GLfloat light_position[] = {1.0, 1.0, 0.0, 0.0};
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        GLfloat material[] = {0.0, 0.0, 1.0, 0.5};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
        GLfloat material2[] = {1.0, 0.0, 0.0, 1.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, material2);

        glTranslatef(scene->player.position.x, scene->player.position.y, scene->player.position.z);
        //glTranslatef(scene->camera.position.x, scene->camera.position.y, scene->camera.position.z);
        glRotatef(scene->player.rotation.y, 0.0f, scene->player.rotation.y, 0.0f);

        glScalef(0.005f, 0.005f, 0.005f);

        draw_player(&(scene->player.player_model));
    glPopMatrix();
}

/*
*                  Basic OpenGL settings compacted into one function
*/
void init_opengl() {

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);

    glClearColor(0.0f, 0.5f, 0.2f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0f, 5.0f, 10.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    );

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
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
