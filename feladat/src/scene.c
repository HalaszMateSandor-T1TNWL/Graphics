#include "Utils/scene.h"

float theta = 45;

/*
*       Initializes the components necessary to the scene
*/
void init_scene(Scene* scene) {
    scene->objects = malloc(sizeof(Entity) * MAX_OBJECTS);

    init_player(&scene->player);
    if(load_model(&scene->player.model, "../assets/Hatsune_Miku/test.obj") == 0) {
        return;
    }
    scene->player.textureID = load_texture("../assets/Hatsune_Miku/test.png");
    printf("TextureID: %d\n", scene->player.textureID);
    calculate_bounding_box(&scene->player);

    init_camera(&scene->camera);

    init_terrain(&scene->terrain, 100, 100);
    scene->terrain.textureID[0] = load_texture("../assets/Ground/grass2.png");

    for(int i = 0; i < MAX_OBJECTS; i++) {
        init_entity(&scene->objects[i]);
    }

    init_skybox(scene);
    generate_terrain(&scene->terrain);

    load_model(&scene->objects[0].model, "../assets/Map/Building.obj");
    scene->objects[0].textureID = load_texture("../assets/Stone_Pillar/pillar.png");
    calculate_bounding_box(&scene->objects[0]);

    load_model(&scene->objects[1].model, "../assets/Fatass/fatass.obj");
    scene->objects[1].textureID = load_texture("../assets/Fatass/eye.png");
    calculate_bounding_box(&scene->objects[1]);

    load_model(&scene->objects[2].model, "../assets/Map/stone_formation.obj");
    scene->objects[2].textureID = load_texture("../assets/Stone_Pillar/pillar.png");
    calculate_bounding_box(&scene->objects[2]);

    load_model(&scene->objects[3].model, "../assets/Map/Pillar/set_piece.obj");
    scene->objects[3].textureID = load_texture("../assets/Stone_Pillar/pillar.png");
    load_model(&scene->objects[4].model, "../assets/Map/Pillar/PILL_main_pillar.obj");
    calculate_bounding_box(&scene->objects[4]);

    scene->light_pos.x = 10.0f;
    scene->light_pos.y = 100.0f;
    scene->light_pos.z = 10.0f;
    scene->brightness = 0.2f;
    scene->is_fog = false;
}

void update_scene(Scene* scene, float speedFPS) {
    scene -> light_pos.x = scene -> light_pos.y * cos(degree_to_radian(theta)) * sin(degree_to_radian(theta));
    scene -> light_pos.z = scene -> light_pos.y * cos(degree_to_radian(theta)) * sin(degree_to_radian(theta));
    theta += 0.01;

    //printf("Light source:\tx: %f\tz: %f\n", scene -> light_pos.x, scene -> light_pos.z);
}


void render_scene(Scene* scene) {
    float playerX = scene->player.position.x;
    float playerY = scene->player.position.y;
    float playerZ = scene->player.position.z;

    float cameraX = scene->camera.position.x;
    float cameraY = scene->camera.position.y;
    float cameraZ = scene->camera.position.z;

    /*if(cameraY < 0.0f) {
        cameraY = 1.0f;
    }*/
    if (scene->camera.distance_from_player < 5.0f) {
        scene->camera.distance_from_player = 5.0f;
    }

    if(scene->is_fog){
        glEnable(GL_FOG);

        float fogColor[4] = {0.8, 0.8, 0.8, 0.2};

        glFogi(GL_FOG_MODE, GL_LINEAR);
        glFogfv(GL_FOG_COLOR, fogColor);

        glFogf(GL_FOG_DENSITY, 0.5);
        glHint(GL_FOG_HINT, GL_NICEST);

        glFogf(GL_FOG_START, 100.0f);
        glFogf(GL_FOG_END, 200);
    } else {
        glDisable(GL_FOG);
    }

    GLfloat light_model[] = {scene->brightness, scene->brightness, scene->brightness, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model);

    GLfloat light_position[] = {scene->light_pos.x, scene->light_pos.y, scene->light_pos.z, 1.0f};

    glColor3f(1.0f, 1.0f, 1.0f);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat spec_mat[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat emission_mat[] = {0.0f, 0.0f, 0.0f, 0.0f};
    GLfloat spec_col[] = {1.0f, 0.5f, 0.1f, 1.0f};
    GLfloat diff_col[] = {0.0f, 0.0f, 0.0f, 1.0f};
    
    /* Setting the projection matrix at the beginning of each frame */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1280.0f / 720.0f, 1.0f, 6000.0f);

    /* Then switching to a modelview for rendering everything */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (
        cameraX, cameraY, cameraZ,
        playerX + 1, playerY + 4, playerZ + 1.5,
        0.0f, 1.0f, 0.0f
    );

    /* Making sure I enable lighting AFTER setting everything, so it doesn't get all funky */
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff_col);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec_col);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec_mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_mat);

    /*  Rendering the player */
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, scene->player.textureID);

        debug_bounding_box(&scene->player.box);
        glTranslatef(scene->player.position.x, scene->player.position.y, scene->player.position.z);
        glRotatef(scene->player.rotation.y, 0.0f, 1.0f, 0.0f);
        glScalef(scene->player.size.x, scene->player.size.y, scene->player.size.z);

        draw_model(&(scene->player.model));
    glPopMatrix();

    /* Rendering objects from the scene */
    /* A house thingy */
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->objects[0].textureID);
        scene->objects[0].position.x = scene->objects[0].box.position.x = 150.0f;
        scene->objects[0].position.y = scene->objects[0].box.position.y = 0.0f;
        scene->objects[0].position.z = scene->objects[0].box.position.z = 200.0f;
		
        scene->objects[0].size.x = 10.0f;
        scene->objects[0].size.y = 10.0f;
        scene->objects[0].size.z = 10.0f;

        debug_bounding_box(&scene->objects[0].box);
        glTranslatef(150.0f, 0.0f, 200.0f);
        draw_model(&scene->objects[0].model);
    glPopMatrix();
    
    /*Fatass Teto plush*/
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->objects[1].textureID);
        scene->objects[1].position.x = scene->objects[1].box.position.x = 100.0f;
        scene->objects[1].position.y = scene->objects[1].box.position.y = 0.0f;
        scene->objects[1].position.z = scene->objects[1].box.position.z = 100.0f;

        scene->objects[1].size.x = 5.0f;
        scene->objects[1].size.y = 15.0f;
        scene->objects[1].size.z = 5.0f;

        debug_bounding_box(&scene->objects[1].box);
        glTranslatef(100.0f, 0.0f, 100.0f);
        draw_model(&scene->objects[1].model);
    glPopMatrix();

    /* Ominous pillar */
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->objects[2].textureID);
        scene->objects[2].position.x = scene->objects[2].box.position.x = 110.0f;
        scene->objects[2].position.y = scene->objects[2].box.position.y = 0.0f;
        scene->objects[2].position.z = scene->objects[2].box.position.z = 110.0f;

        scene->objects[2].size.x = 2.5f;
        scene->objects[2].size.y = 45.0f;
        scene->objects[2].size.z = 2.5f;

        debug_bounding_box(&scene->objects[2].box);
        glTranslatef(110.0f, 0.0f, 110.0f);
        draw_model(&scene->objects[2].model);
    glPopMatrix();

    /* Rendering a set piece pillar (no collison) */
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->objects[3].textureID);
        scene->objects[3].position.x = scene->objects[4].box.position.x = 150.0f;
        scene->objects[3].position.y = scene->objects[4].box.position.y = 0.0f;
        scene->objects[3].position.z = scene->objects[4].box.position.z = 100.0f;

        scene->objects[3].size.x = 2.5f;
        scene->objects[3].size.y = 45.0f;
        scene->objects[3].size.z = 2.5f;

        glTranslatef(150.0f, 0.0f, 100.0f);
        draw_model(&scene->objects[3].model);
    glPopMatrix();

    /* Rendering the terrain */
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->terrain.textureID[0]);
        glEnable(GL_TEXTURE_2D);
        render_terrain(&scene->terrain);
    glPopMatrix();

    /* Rendering the skybox and making sure it follows the camera so you can never leave it */
    glPushMatrix();
        glTranslatef(scene->camera.position.x, scene->camera.position.y, scene->camera.position.z);
        draw_skybox(scene, 5000);
    glPopMatrix();
}

void init_opengl() {

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_LIGHTING);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);

    glClearColor(0.0f, 0.5f, 0.2f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);

}

void init_skybox(Scene* scene) {
    scene->skybox[SKY_LEFT] = load_texture("../assets/Skybox/left.png");
    scene->skybox[SKY_BACK] = load_texture("../assets/Skybox/back.png");
    scene->skybox[SKY_RIGHT] = load_texture("../assets/Skybox/right.png");
    scene->skybox[SKY_FRONT] = load_texture("../assets/Skybox/front.png");
    scene->skybox[SKY_TOP] = load_texture("../assets/Skybox/top.png");
    scene->skybox[SKY_BOTTOM] = load_texture("../assets/Skybox/down.png");
}

void draw_skybox(Scene* scene, float size) {
    glBindTexture(GL_TEXTURE_2D, scene->skybox[SKY_BOTTOM]);
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

    glBindTexture(GL_TEXTURE_2D, scene->skybox[SKY_RIGHT]);
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

    glBindTexture(GL_TEXTURE_2D,scene->skybox[SKY_LEFT]);
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

    glBindTexture(GL_TEXTURE_2D, scene->skybox[SKY_BACK]);
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
