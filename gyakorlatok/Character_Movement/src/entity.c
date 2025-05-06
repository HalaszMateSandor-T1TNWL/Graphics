#include "Environment/entity.h"

/*
*                               Self explenatory really
*/
void init_entity(Entity* entity) {

    entity->move_speed = 0.0f;
    entity->turn_speed = 0.0f;
    entity->upwards_speed = 0.0f;

    entity->position.x = 100.0f;
    entity->position.y = 0.0f;
    entity->position.z = 100.0f;

    entity->rotation.x = 0.0f;
    entity->rotation.y = 0.0f;
    entity->rotation.z = 0.0f;

    entity->is_in_air = false;
    entity->jumped = 0;

    init_bounding_box(&entity->box);
}

void init_player(Entity* player) {
    player->move_speed = 0.0f;
    player->turn_speed = 0.0f;
    player->upwards_speed = 0.0f;

    player->position.x = 100.0f;
    player->position.y = 0.0f;
    player->position.z = 100.0f;

    player->rotation.x = 0.0f;
    player->rotation.y = 0.0f;
    player->rotation.z = 0.0f;

    player->size.x = 0.5f;
    player->size.y = 0.5f;
    player->size.z = 0.5f;

    player->is_in_air = false;
    player->jumped = 0;

    init_bounding_box(&entity->box);
}


/*
*          It's important to set the entity's speed to frames per second
*      otherwise once/IF the game starts lagging or running slower the entity
*                           will move slower as well.
*/
void move(Entity* entity, float speed_FPS) {
    get_speed(entity);

    entity->rotation.y += entity->turn_speed * speed_FPS;

    float distance = entity->move_speed * speed_FPS;
    float dx = distance * sin(degree_to_radian(entity->rotation.y));
    float dz = distance * cos(degree_to_radian(entity->rotation.y));

    increase_position(entity, dx, 0, dz);

    entity->upwards_speed += GRAVITY * speed_FPS;
    increase_position(entity, 0, entity->upwards_speed * speed_FPS, 0);
    
    if (entity->position.y < TERRAIN_HEIGHT) {
        entity->upwards_speed = 0;
        entity->is_in_air = false;
        entity->jumped = 0;
        entity->position.y = TERRAIN_HEIGHT;
    }
    /*printf("entity vertical position: %f\n", entity->position.y);
    printf("Rotation Y: %f, dx: %f, dz: %f\n", entity->rotation.y, dx, dz);
    printf("Turn Speed: %f, Movespeed: %f\n", entity->turn_speed, entity->move_speed);*/
}

/*
*              Two simple functions of setting the entitys positionand rotation
*           (basically just helper functions, so the move function isn't as cramped)
*/
void increase_position(Entity* entity, float dx, float dy, float dz) {
    entity->position.x += dx;
    entity->position.y += dy;
    entity->position.z += dz;
}
void increase_rotation(Entity* entity, float dx, float dy, float dz) {
    entity->rotation.x += dx;
    entity->rotation.y += dy;
    entity->rotation.z += dz;
}

/*
*       A function for setting the entity's speed depending on which button they press
*/
void get_speed(Entity* entity)
{
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);
    
    if (keyboard[SDL_SCANCODE_W]) {
        entity->move_speed = RUN_SPEED;
    } else if (keyboard[SDL_SCANCODE_S]) {
        entity->move_speed = -RUN_SPEED;
    } else{
        entity->move_speed = 0;
    }

    if (keyboard[SDL_SCANCODE_A]) {
        entity->turn_speed = TURN_SPEED;
    }else if (keyboard[SDL_SCANCODE_D]) {
        entity->turn_speed = -TURN_SPEED;
    } else{
        entity->turn_speed = 0;
    }

    /* This is a really cheaty way of solving double jumping, but I couldn't think of anything else :[ */
    if(keyboard[SDL_SCANCODE_SPACE]){
        if(entity->jumped == 0){
            entity->is_in_air = true;
            entity->jumped++;
            entity->upwards_speed = JUMP_POWER;
            //printf("Jumping\nJumped: %d\n", entity->jumped);
        } else if(entity->jumped < 10 && entity->is_in_air) {
            entity->jumped++;
            entity->upwards_speed = JUMP_POWER;
            //printf("Jumping\nJumped: %d\n", entity->jumped);
        }
    }
}

void calculate_bounding_box(Entity* entity) {

    for(int i = 0; i < entity->model.n_vertices; i++) {
        if(entity->model.vertices[i].x < entity->box.min_x) entity->box.min_x = entity->model.vertices[i].x;
        if(entity->model.vertices[i].x > entity->box.max_x) entity->box.max_x = entity->model.vertices[i].x;

        if(entity->model.vertices[i].y < entity->box.min_y) entity->box.min_y = entity->model.vertices[i].y;
        if(entity->model.vertices[i].y > entity->box.max_y) entity->box.max_y = entity->model.vertices[i].y;

        if(entity->model.vertices[i].z < entity->box.min_z) entity->box.min_z = entity->model.vertices[i].z;
        if(entity->model.vertices[i].z > entity->box.max_z) entity->box.max_z = entity->model.vertices[i].z;
    }

    /*entity->box.size.x = entity->box.max_x - entity->box.min_x;
    entity->box.size.y = entity->box.max_y - entity->box.min_y;
    entity->box.size.z = entity->box.max_z - entity->box.min_z;

    entity->box.center.x = (entity->box.max_x + entity->box.min_x) / 2;
    entity->box.center.y = (entity->box.max_y + entity->box.min_y) / 2;
    entity->box.center.z = (entity->box.max_z + entity->box.min_z) / 2;*/

    //printf("Bounds are:\n[%f :: %f]\n[%f :: %f]\n[%f :: %f]\n", entity->box.min_x, entity->box.max_x, entity->box.min_y, entity->box.max_y, entity->box.min_z, entity->box.max_z);
}

void load_entity_model(Entity* entity) {
    load_model(&entity->model, "../textures/Hatsune_Miku/test.obj");
}

void free_entity(Entity* entity) {
    free_model(&entity->model);
    glDeleteTextures(1, &entity->textureID);
}

