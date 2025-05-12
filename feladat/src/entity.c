#include "Environment/entity.h"

/*
*                               Self explenatory really
*/
void init_entity(Entity* entity) {

    entity->move_speed = 0.0f;
    entity->turn_speed = 0.0f;
    entity->upwards_speed = 0.0f;

    entity->position.x = 0.0f;
    entity->position.y = 0.0f;
    entity->position.z = 0.0f;

    entity->rotation.x = 0.0f;
    entity->rotation.y = 0.0f;
    entity->rotation.z = 0.0f;

    entity->size.x = 1.0f;
    entity->size.y = 1.0f;
    entity->size.z = 1.0f;

    entity->is_in_air = false;
    entity->jumped = 0;

    init_bounding_box(&entity->box);
    init_model(&entity->model);
}

void init_player(Entity* entity) {

    entity->move_speed = 0.0f;
    entity->turn_speed = 0.0f;
    entity->upwards_speed = 0.0f;

    entity->position.x = entity->box.position.x = 10.0f;
    entity->position.y = entity->box.position.y = 10.0f;
    entity->position.z = entity->box.position.z = 100.0f;

    entity->rotation.x = 0.0f;
    entity->rotation.y = 0.0f;
    entity->rotation.z = 0.0f;

    entity->size.x = 1.5f;
    entity->size.y = 1.5f;
    entity->size.z = 1.5f;

    entity->is_in_air = false;
    entity->jumped = 0;

    init_bounding_box(&entity->box);
    init_model(&entity->model);
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
	float dy = GRAVITY * speed_FPS;
    increase_position(entity, dx, 0, dz);

    entity->upwards_speed += dy;
    increase_position(entity, 0, entity->upwards_speed * speed_FPS, 0);
	
	vec3 offset;
	offset.x = dx;
	offset.y = 0.0f;
	offset.z = dz;
	
	update_bounding_box(&entity->box, offset, speed_FPS);
}

void handle_collision(Entity* object, Entity* player) {
    float overlapX = fmin(player->box.max_x, object->box.max_x) - fmax(player->box.min_x, object->box.min_x);
    float overlapY = fmin(player->box.max_y, object->box.max_y) - fmax(player->box.min_y, object->box.min_y);
    float overlapZ = fmin(player->box.max_z, object->box.max_z) - fmax(player->box.min_z, object->box.min_z);

	if(overlapX < overlapY && overlapX < overlapZ) {
		if(player->position.x < object->position.x) {
			player->position.x -= overlapX;
		} else{
			player->position.x += overlapX;
		}
	} else if (overlapY < overlapZ) {
		if(player->position.y < object->position.y) {
			player->position.y -= overlapY;
		} else{
			player->position.y += overlapY;
			player->upwards_speed = 0;
			player->is_in_air = false;
			player->jumped = 0;
		}
	} else{
		if(player->position.z < object->position.z) {
			player->position.z -= overlapZ;
		} else{
			player->position.z += overlapZ;
		}
	}
}

/*
*              Two simple functions of setting the entitys position and rotation
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

    /* This is a really cheaty way of solving double jumping, but I couldn't think of anything else :[ 
    *           EDIT: nvm, you actually have long jumps with this, this was intentional
    */
    if(keyboard[SDL_SCANCODE_SPACE]){
        if(entity->jumped == 0){
            entity->is_in_air = true;
            entity->jumped++;
            entity->upwards_speed = JUMP_POWER;
        } else if(entity->jumped < 10 && entity->is_in_air) {
            entity->jumped++;
            entity->upwards_speed = JUMP_POWER;
        }
    }
}

void calculate_bounding_box(Entity* entity) {
    if(&entity->model == NULL || entity->model.vertices == NULL || entity->model.n_vertices <= 0){
        fprintf(stderr, "Model doesn't exist\n");
        return;
    }

    for(int i = 0; i < entity->model.n_vertices; i++) {

        if(i < 0 || i >= entity->model.n_vertices) {
            fprintf(stderr, "Tried accessing vertices out of bounds at index: %d\n", i);
            return;
        }

        if(entity->model.vertices[i].x < entity->box.min_x) entity->box.min_x = entity->model.vertices[i].x;
        if(entity->model.vertices[i].x > entity->box.max_x) entity->box.max_x = entity->model.vertices[i].x;
        if(entity->model.vertices[i].y < entity->box.min_y) entity->box.min_y = entity->model.vertices[i].y;
        if(entity->model.vertices[i].y > entity->box.max_y) entity->box.max_y = entity->model.vertices[i].y;
        if(entity->model.vertices[i].z < entity->box.min_z) entity->box.min_z = entity->model.vertices[i].z;
        if(entity->model.vertices[i].z > entity->box.max_z) entity->box.max_z = entity->model.vertices[i].z;
    }

    entity->box.size.x = (entity->box.max_x - entity->box.min_x);
    entity->box.size.y = (entity->box.max_y - entity->box.min_y);
    entity->box.size.z = (entity->box.max_z - entity->box.min_z);

    entity->box.center.x = (entity->box.max_x + entity->box.min_x) / 2;
    entity->box.center.y = (entity->box.max_y + entity->box.min_y) / 2;
    entity->box.center.z = (entity->box.max_z + entity->box.min_z) / 2;

    printf("Bounding Box: Min(%f, %f, %f), Max(%f, %f, %f)\n",
           entity->box.min_x, entity->box.min_y, entity->box.min_z,
           entity->box.max_x, entity->box.max_y, entity->box.max_z);

    
}

void free_entity(Entity* entity) {
    free_model(&entity->model);
    glDeleteTextures(1, &entity->textureID);
}

