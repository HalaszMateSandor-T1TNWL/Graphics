#include <stdio.h>
#include "Brick/Brick.h"

void set_size(Brick* brick){
    int ok = 0;
    int x, y, z;
    printf("Please enter the dimensions of the brick.\n");
    do
    {
        ok = 1;
        printf("x: ");
        if(scanf("%d", &x) != 1 || x <= 0){
            printf("Please only enter numbers.\n");
            while(getchar() != '\n');
            continue; // <- For restarting the loop (basically skips everything else)
        }

        printf("y: ");
        if(scanf("%d", &y) != 1 || y <= 0){
            printf("Please only enter numbers.\n");
            while(getchar() != '\n');
            continue;
        }

        printf("z: ");
        if(scanf("%d", &z) != 1 || z <= 0){
            printf("Please only enter numbers.\n");
            while(getchar() != '\n');
            continue;
        }

        if(x > 0 && y > 0 && z > 0){
            brick->x = x;
            brick->y = y;
            brick->z = z;
            ok = 0;
        }
    } while (ok == 1);

    printf("Dimension successfully set.\n");
}

void calc_volume(Brick* brick){
    int volume = brick->x * brick->y * brick->z;
    printf("Volume: %d\n", volume);
}

void calc_surface(Brick* brick){
    int surface = 2 * (brick->x * brick->y + brick->x * brick->z + brick->y * brick->z);
    printf("Surface: %d\n", surface);
}

void is_there_square(Brick* brick){
    if(brick->x == brick->y || brick->x == brick->z || brick->y == brick->z){
        printf("There is a square face.\n");
    } else {
        printf("There is no square face.\n");
    }
}