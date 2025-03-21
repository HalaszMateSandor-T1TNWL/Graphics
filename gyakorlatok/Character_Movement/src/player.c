#include "../include/Environment/player.h"

const float RUN_SPEED = 20;
const float TURN_SPEED = 160;
const float GRAVITY = -50;
const float JUMP_POWER = 20;
const float TERRAIN_HEIGHT = 0;

void init_player(Player* player){
    player->move_speed = 0.0f;
    player->turn_speed = 0.0f;
    player->upwards_speed = 0.0f;

    player->position.x = 0.0f;
    player->position.y = 0.0f;
    player->position.z = 0.2f;

    player->rotation.x = 0.0f;
    player->rotation.y = 0.0f;
    player->rotation.z = 0.0f;

    player->scale = 1;
}

void move(Player* player, SDL_Event event, double speed_FPS){
    get_speed(player, event);

    increase_rotation(player, 0, player->turn_speed * speed_FPS, 0);

    float distance = player->move_speed * speed_FPS;
    float dx = distance * sin(degree_to_radian(player->rotation.y));
    float dz = distance * cos(degree_to_radian(player->rotation.y));

    increase_position(player, dx, 0, dz);

    player->upwards_speed += GRAVITY * speed_FPS;
    increase_position(player, 0, player->upwards_speed * speed_FPS, 0);
    if (player->position.y < TERRAIN_HEIGHT){
        player->upwards_speed = 0;
        player->position.y = TERRAIN_HEIGHT;
    }
}

void increase_position(Player* player, float dx, float dy, float dz){
    player->position.x += dx;
    player->position.y += dy;
    player->position.z += dz;
}

void increase_rotation(Player* player, float dx, float dy, float dz){
    player->rotation.x += dx;
    player->rotation.y += dy;
    player->rotation.z += dz;
}

void get_speed(Player* player, SDL_Event event){
    switch (event.key.keysym.sym)
    {
    case SDLK_w:
        player->move_speed = RUN_SPEED;
        printf("Forward\n");
        break;
    case SDLK_s:
        player->move_speed = -RUN_SPEED;
        printf("Backwards\n");
        break;
    case SDLK_a:
        player->turn_speed = TURN_SPEED;
        printf("Left\n");
        break;
    case SDLK_d:
        player->turn_speed = -TURN_SPEED;
        printf("Right\n");
        break;
    case SDLK_SPACE:
        player->upwards_speed = JUMP_POWER;
        printf("Jump!\n");
    default:
        player->move_speed = 0;
        player->turn_speed = 0;
        break;
    }
}