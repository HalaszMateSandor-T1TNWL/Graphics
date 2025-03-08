#include <stdio.h>
#include <stdlib.h>
#include "Brick/Brick.h"

int main(int argc, char** argv[]){
    Brick brick;

    set_size(&brick);
    calc_volume(&brick);
    calc_surface(&brick);
    is_there_square(&brick);

    return 0;
}
