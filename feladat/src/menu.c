#include "Utils/menu.h"

int show_menu(SDL_Window* screen, TTF_Font* font){
    Uint32 time;
    int x, y;
    const int NUMMENU = 2;
    const char* labels[NUMMENU] = {"Continue","Exit"};
    SDL_Surface* menus[NUMMENU];
    bool selected[NUMMENU] = {0,0};
    SDL_Color color[2] = {{255,255,255},{255,0,0}};
    
    menus[0] = TTF_RenderText_Solid(font,labels[0],color[0]);
    menus[1] = TTF_RenderText_Solid(font,labels[1],color[0]);
    SDL_Rect pos[NUMMENU];

    int w,h;
    SDL_GetWindowSize(screen, &w, &h);
    pos[0].x = w/2 - menus[0]->clip_rect.w/2;
    pos[0].y = h/2 - menus[0]->clip_rect.h;
    pos[1].x = w/2 - menus[0]->clip_rect.w/2;
    pos[1].y = h/2 + menus[0]->clip_rect.h;
    
    
    SDL_FillRect(screen, &screen->clip_rect ,SDL_MapRGB(screen->format,0x00,0x00,0x00));
 
    SDL_Event event;


}