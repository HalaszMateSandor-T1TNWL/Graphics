#ifndef BRICK_H_
#define BRICK_H_

typedef struct{
    int x;
    int y;
    int z;
} Brick;

void set_size(Brick* brick);
void calc_volume(Brick* brick);
void calc_surface(Brick* brick);
void is_there_square(Brick* brick);

#endif