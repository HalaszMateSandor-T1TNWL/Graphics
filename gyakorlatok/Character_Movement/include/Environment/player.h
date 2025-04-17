#ifndef PLAYER_H_
#define PLAYER_H_

#include "Utils/utils.h"
#include "Environment/load_texture.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <obj/info.h>

#include <GL/gl.h>

#include <SDL2/SDL.h>
#include <stdbool.h>

#define RUN_SPEED 20     //}
#define GRAVITY -50      //} <- Ticks per second
#define JUMP_POWER 20    //}
#define TURN_SPEED 160   //<- Degrees per second
#define TERRAIN_HEIGHT 0 // This is a placeholder, will implement an actual ground searching algorithm thingamajig


typedef struct Player
{
    Model player_model;
    GLuint textureID;

    vec3 position;
    vec3 rotation;

    float move_speed;
    float turn_speed;
    float upwards_speed;
    
    int jumped;
    bool is_in_air;

    float scale;
} Player;

/* Initializes the player with default values */
void init_player(Player* player);

/* Moves the player around */
void move(Player* player, float speed_FPS);

/* Moves the player around according to the given values */
void increase_position(Player* player, float dx, float dy, float dz);

/* Rotates the player around according to the given values */
void increase_rotation(Player* player, float dx, float dy, float dz);

/* Gets the input and determines how fast the player will be moving */
void get_speed(Player* player);

/* Loads in a model for use */
void load_player_model(Player* player);


#endif /*PLAYER_H_*/