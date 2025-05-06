#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct Menu {
    int x,y;
    int w,h;
    bool is_selected;
    char label;
    SDL_Surface menu;
    SDL_Color color[2];
} Menu;

int show_menu(Menu* menu, SDL_Window* window, TTF_Font* font);

void init_menu(Menu* menu);

#endif /* MENU_H_ */