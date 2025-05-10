#include "Utils/scene.h"

/*
*       Initializes the components necessary to the scene
*/
void init_scene(Scene* scene) {
    scene->objects = malloc(sizeof(Entity) * 4);

    init_player(&scene->player);
    if(load_model(&scene->player.model, "../textures/Hatsune_Miku/test.obj") == 0) {
        return;
    }
    scene->player.textureID = load_texture("../textures/Hatsune_Miku/test.png");
    printf("TextureID: %d\n", scene->player.textureID);
    calculate_bounding_box(&scene->player);

    init_camera(&scene->camera);

    init_terrain(&scene->terrain, 100, 100);
    scene->terrain.textureID[0] = load_texture("../textures/Ground/grass2.png");

    for(int i = 0; i < 4; i++) {
        init_entity(&scene->objects[i]);
    }

    load_model(&scene->objects[0].model, "../textures/Map/Building.obj");
    scene->objects[0].textureID = load_texture("../textures/Stone_Pillar/pillar.png");
    calculate_bounding_box(&scene->objects[0]);

    load_model(&scene->objects[1].model, "../textures/Fatass/fatass02.obj");
    scene->objects[1].textureID = load_texture("../textures/Fatass/eye.png");
    calculate_bounding_box(&scene->objects[1]);


    init_skybox(scene);
    generate_terrain(&scene->terrain);

    scene->light_pos.x = 100.0f;
    scene->light_pos.y = 100.0f;
    scene->light_pos.z = 100.0f;
}

void update_scene(Scene* scene, float speedFPS) {


}

/*
*           A function for rendering everything necessary to the world
*/
void render_scene(Scene* scene) {
    float playerX = scene->player.position.x;
    float playerY = scene->player.position.y;
    float playerZ = scene->player.position.z;

    float cameraX = scene->camera.position.x;
    float cameraY = scene->camera.position.y;
    float cameraZ = scene->camera.position.z;

    /* Setting the projection matrix at the beginning of each frame */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1280.0f / 720.0f, 0.1f, 6000.0f);

    /* Then switching to a modelview for rendering everything */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (
        cameraX, cameraY, cameraZ,
        playerX, playerY + 4, playerZ + 2,
        0.0f, 1.0f, 0.0f
    );

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = {scene->light_pos.x, scene->light_pos.y, scene->light_pos.z, 0.5};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    /*  Rendering the player */
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, scene->player.textureID);

        GLfloat material[] = {1.0, 1.0, 1.0, 0.5};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material);

        GLfloat material2[] = {1.0, 1.0, 1.0, 1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material2);

        debug_bounding_box(&scene->player.box);
        glTranslatef(scene->player.position.x, scene->player.position.y, scene->player.position.z);
        glRotatef(scene->player.rotation.y, 0.0f, 1.0f, 0.0f);
        glScalef(0.025, 0.025, 0.025);

        draw_player(&(scene->player.model));
    glPopMatrix();

    /* Rendering objects from the scene */
    /* A grass house thingy */
    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material);

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material2);

        glBindTexture(GL_TEXTURE_2D, scene->objects[0].textureID);
        scene->objects[0].position.x = 10.0f;
        scene->objects[0].position.y = 0.0f;
        scene->objects[0].position.z = 100.0f;
        scene->objects[0].size.x = 20.0f;
        scene->objects[0].size.y = 20.0f;
        scene->objects[0].size.z = 20.0f;
        debug_bounding_box(&scene->objects[0].box);
        glTranslatef(10.0f, 0.0f, 100.0f);
        draw_model(&scene->objects[0].model);
    glPopMatrix();
    
    /* A cheese goat, a goat cheese if you will */
    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material2);

        glBindTexture(GL_TEXTURE_2D, scene->objects[1].textureID);
        scene->objects[1].position.x = 100.0f; 
        scene->objects[1].position.y = 0.0f;
        scene->objects[1].position.z = 100.0f;

        scene->objects[1].size.x = 5.0f;
        scene->objects[1].size.y = 15.0f;
        scene->objects[1].size.z = 5.0f;

        debug_bounding_box(&scene->objects[1].box);
        glTranslatef(100.0f, 0.0f, 100.0f);
        draw_model(&scene->objects[1].model);
    glPopMatrix();

    /* Rendering the terrain */
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->terrain.textureID[0]);
        glEnable(GL_TEXTURE_2D);

        GLfloat grass_mat_diff[] = {10.0, 1.0, 1.0, 1.0};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, grass_mat_diff);

        GLfloat grass_mat_amb[] = {1.0, 1.0, 5.0, 1.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, grass_mat_amb);
        
        //glTranslatef(-650.0f, 0.0f, -650.0f);
        render_terrain(&scene->terrain);
    glPopMatrix();

    glPushMatrix();
        draw_skybox(scene, 5000);
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
    glClearDepth(10.0f);

}


/*
*                       A function for drawing the loaded in player model 
*                           by itterating over each read in vertex
*/
void draw_player(const Model* model) {
    int i, k;
    int vertex_index, texture_index, normal_index;
    float x, y, z, u, v;

    glBegin(GL_TRIANGLES);

    for (i = 0; i < model->n_triangles; i++) {
        for (k = 0; k < 3; k++) {
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

void init_skybox(Scene* scene) {
    scene->skybox[SKY_LEFT] = load_texture("../textures/Skybox/left.png");
    scene->skybox[SKY_BACK] = load_texture("../textures/Skybox/back.png");
    scene->skybox[SKY_RIGHT] = load_texture("../textures/Skybox/right.png");
    scene->skybox[SKY_FRONT] = load_texture("../textures/Skybox/front.png");
    scene->skybox[SKY_TOP] = load_texture("../textures/Skybox/top.png");
    scene->skybox[SKY_BOTTOM] = load_texture("../textures/Skybox/down.png");
}

void draw_skybox(Scene* scene, float size) {
    glBindTexture(GL_TEXTURE_2D, scene->skybox[SKY_BACK]);
    //back face
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(size/2,size/2,size/2);
        glTexCoord2f(1,0);
        glVertex3f(-size/2,size/2,size/2);
        glTexCoord2f(1,1);
        glVertex3f(-size/2,-size/2,size/2);
        glTexCoord2f(0,1);
        glVertex3f(size/2,-size/2,size/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, scene->skybox[SKY_LEFT]);
    //left face
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-size/2,size/2,size/2);
        glTexCoord2f(1,0);
        glVertex3f(-size/2,size/2,-size/2);
        glTexCoord2f(1,1);
        glVertex3f(-size/2,-size/2,-size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,-size/2,size/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, scene->skybox[SKY_FRONT]);
    //front face
    glBegin(GL_QUADS);
        glTexCoord2f(1,0);
        glVertex3f(size/2,size/2,-size/2);
        glTexCoord2f(0,0);
        glVertex3f(-size/2,size/2,-size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,-size/2,-size/2);
        glTexCoord2f(1,1);
        glVertex3f(size/2,-size/2,-size/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D,scene->skybox[SKY_RIGHT]);
    //right face
    glBegin(GL_QUADS);  
        glTexCoord2f(0,0);
        glVertex3f(size/2,size/2,-size/2);
        glTexCoord2f(1,0);
        glVertex3f(size/2,size/2,size/2);
        glTexCoord2f(1,1);
        glVertex3f(size/2,-size/2,size/2);
        glTexCoord2f(0,1);
        glVertex3f(size/2,-size/2,-size/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, scene->skybox[SKY_TOP]);
    //top face   
    glBegin(GL_QUADS);
        glTexCoord2f(1,0);
        glVertex3f(size/2,size/2,size/2);
        glTexCoord2f(0,0);
        glVertex3f(-size/2,size/2,size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,size/2,-size/2);
        glTexCoord2f(1,1);
        glVertex3f(size/2,size/2,-size/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, scene->skybox[SKY_BOTTOM]);        
    //bottom face
    glBegin(GL_QUADS);  
        glTexCoord2f(1,1);
        glVertex3f(size/2,-size/2,size/2);
        glTexCoord2f(0,1);
        glVertex3f(-size/2,-size/2,size/2);
        glTexCoord2f(0,0);
        glVertex3f(-size/2,-size/2,-size/2);
        glTexCoord2f(1,0);
        glVertex3f(size/2,-size/2,-size/2);
    glEnd();
}

void free_skybox(Scene* scene) {
    glDeleteTextures(6, &scene->skybox[0]);
}
