#include "Environment/player.h"

/*
*                               Self explenatory really
*/
void init_player(Player* player) {

    player->move_speed = 0.0f;
    player->turn_speed = 0.0f;
    player->upwards_speed = 0.0f;

    player->position.x = 100.0f;
    player->position.y = 0.0f;
    player->position.z = 100.0f;

    player->rotation.x = 0.0f;
    player->rotation.y = 0.0f;
    player->rotation.z = 0.0f;

    player->is_in_air = false;
    player->jumped = 0;

    player->scale = 1;

    load_player_model(player);
    print_model_info(&player->player_model);
}


/*
*          It's important to set the player's speed to frames per second
*      otherwise once/IF the game starts lagging or running slower the player
*                           will move slower as well.
*/
void move(Player* player, float speed_FPS) {
    // Gets user input and converts them to movement
    get_speed(player);

    // Rotate the player smoothly (to the left or right)
    player->rotation.y += player->turn_speed * speed_FPS;

    float distance = player->move_speed * speed_FPS;
    float dx = distance * sin(degree_to_radian(player->rotation.y));
    float dz = distance * cos(degree_to_radian(player->rotation.y));

    increase_position(player, dx, 0, dz);

    player->upwards_speed += GRAVITY * speed_FPS;
    increase_position(player, 0, player->upwards_speed * speed_FPS, 0);
    
    if (player->position.y < TERRAIN_HEIGHT) {
        player->upwards_speed = 0;
        player->is_in_air = false;
        player->jumped = 0;
        player->position.y = TERRAIN_HEIGHT;
    }
    /*printf("Player vertical position: %f\n", player->position.y);
    printf("Rotation Y: %f, dx: %f, dz: %f\n", player->rotation.y, dx, dz);
    printf("Turn Speed: %f, Movespeed: %f\n", player->turn_speed, player->move_speed);*/
}

/*
*              Two simple functions of setting the players positionand rotation
*           (basically just helper functions, so the move function isn't as cramped)
*/
void increase_position(Player* player, float dx, float dy, float dz) {
    player->position.x += dx;
    player->position.y += dy;
    player->position.z += dz;
}
void increase_rotation(Player* player, float dx, float dy, float dz) {
    player->rotation.x += dx;
    player->rotation.y += dy;
    player->rotation.z += dz;
}

/*
*       A function for setting the player's speed depending on which button they press
*/
void get_speed(Player* player)
{
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);
    
    if (keyboard[SDL_SCANCODE_W]) {
        player->move_speed = RUN_SPEED;
    } else if (keyboard[SDL_SCANCODE_S]) {
        player->move_speed = -RUN_SPEED;
    } else{
        player->move_speed = 0;
    }

    if (keyboard[SDL_SCANCODE_A]) {
        player->turn_speed = TURN_SPEED;
    }else if (keyboard[SDL_SCANCODE_D]) {
        player->turn_speed = -TURN_SPEED;
    } else{
        player->turn_speed = 0;
    }

    /* This is a really cheaty way of solving double jumping, but I couldn't think of anything else :[ */
    if(keyboard[SDL_SCANCODE_SPACE]){
        if(player->jumped == 0){
            player->is_in_air = true;
            player->jumped++;
            player->upwards_speed = JUMP_POWER;
            //printf("Jumping\nJumped: %d\n", player->jumped);
        } else if(/*player->jumped < 6 &&*/ player->is_in_air) {
            player->jumped++;
            player->upwards_speed = JUMP_POWER;
            //printf("Jumping\nJumped: %d\n", player->jumped);
        }
    }
}

void load_player_model(Player* player) {
    load_model(&player->player_model, "../textures/Hatsune_Miku/test.obj");
}

void free_player(Player* player) {
    free_model(&player->player_model);
    glDeleteTextures(1, &player->textureID);
}