#ifndef PLAYER_H_
#define PLAYER_H_

#include <SDL2/SDL.h>
#include "../Utils/utils.h"

typedef struct Player
{
    vec3 position;
    vec3 rotation;

    float move_speed;
    float turn_speed;
    float upwards_speed;

    float scale;
} Player;

/* Initializes the player with default values */
void init_player(Player* player);

/* Moves the player around */
void move(Player* player, SDL_Event event, double speed_FPS);

/* Moves the player around according to the given values */
void increase_position(Player* player, float dx, float dy, float dz);

/* Rotates the player around according to the given values */
void increase_rotation(Player* player, float dx, float dy, float dz);

/* Gets the input and determines how fast the player will be moving */
void get_speed(Player* player, SDL_Event event);

#endif