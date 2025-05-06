#ifndef PLAYER_H_
#define PLAYER_H_

#include "Utils/utils.h"
#include "Environment/load_texture.h"
#include "Utils/bounding_box.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <obj/info.h>

#include <GL/gl.h>

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>

#define RUN_SPEED 20     //}
#define GRAVITY -50      //} <- Ticks per second
#define JUMP_POWER 25    //}
#define TURN_SPEED 160   //<- Degrees per second
#define TERRAIN_HEIGHT 0 // This is a placeholder, will implement an actual ground searching algorithm thingamajig

typedef struct Entity {
    Model model;
    GLuint textureID;

    vec3 position;
    vec3 rotation;

    float move_speed;
    float turn_speed;
    float upwards_speed;
    
    int jumped;
    bool is_in_air;
    Bounding_Box box;

} Entity;

/* Initializes the entity with default values */
void init_entity(Entity* entity);
void init_player(Entity* player);

/* Moves the entity around */
void move(Entity* entity, float speed_FPS);

/* Moves the entity around according to the given values */
void increase_position(Entity* entity, float dx, float dy, float dz);

/* Rotates the entity around according to the given values */
void increase_rotation(Entity* entity, float dx, float dy, float dz);

/* Gets the input and determines how fast the entity will be moving */
void get_speed(Entity* entity);

/* Loads in a model for use */
void load_entity_model(Entity* entity);

/* Calculating the bounds of the box surrounding the model */
void calculate_bounding_box(Entity* entity);

/* Frees up memory allocated towards the entity entity */
void free_entity(Entity* entity);


#endif /*PLAYER_H_*/