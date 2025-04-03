#include "../include/Environment/player.h"

/*
*                               Self explenatory really
*/
void init_player(Player* player){

    player->move_speed = 0.0f;
    player->turn_speed = 0.0f;
    player->upwards_speed = 0.0f;

    player->position.x = 0.0f;
    player->position.y = 0.0f;
    player->position.z = -0.5f;

    player->rotation.x = 0.0f;
    player->rotation.y = 0.0f;
    player->rotation.z = 0.0f;

    player->is_in_air = false;
    player->jumped = 0;

    player->scale = 1;

    init_model(&player->player_model);
    allocate_model(&player->player_model);
}


/*
*          It's important to set the player's speed to frames per second
*      otherwise once/IF the game starts lagging or running slower the player
*                           will move slower as well.
*/
void move(Player* player, SDL_Event event, double speed_FPS){
    get_speed(player, event);

    increase_rotation(player, 0, player->turn_speed * speed_FPS, 0);

    float distance = player->move_speed * speed_FPS;
    float dx = distance * sin(degree_to_radian(player->rotation.y));
    float dz = distance * cos(degree_to_radian(player->rotation.y));

    increase_position(player, dx, 0, dz);
    printf("player position: %f :: %f\n", player->position.x, player->position.z);

    player->upwards_speed += GRAVITY * speed_FPS;
    increase_position(player, 0, player->upwards_speed * speed_FPS, 0);
    
    if (player->position.y < TERRAIN_HEIGHT){
        player->upwards_speed = 0;
        player->is_in_air = false;
        player->jumped = 0;
        player->position.y = TERRAIN_HEIGHT;
    }
    printf("player vertical position: %f\n", player->position.y);
}

/*
*              Two simple functions of setting the players positionand rotation
*           (basically just helper functions, so the move function isn't as cramped)
*/
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

/*
*       A function for setting the player's speed depending on which button they press
*/
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
        player->is_in_air = true;
        if(player->jumped < 2){
            player->upwards_speed = JUMP_POWER;
            player->jumped ++;
            printf("Jump!\n");
            printf("Player has jumped: %d times\n", player->jumped);
        }
        break;
    default:
        player->move_speed = 0;
        player->turn_speed = 0;
        break;
    }
}

void load_player_model(Player* player){
    load_model(&player->player_model, "../textures/Hatsune_Miku/HatsuneMiku.obj");
}