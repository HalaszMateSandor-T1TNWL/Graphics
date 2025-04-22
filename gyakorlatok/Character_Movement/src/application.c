#include "Utils/application.h"

void init_application(App* app) {
    int error_code;

    app->is_running = 0;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if(error_code != 0){
        printf("%s", SDL_GetError());
        return;
    }

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    app->window = SDL_CreateWindow("Character Movement",
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                    1280, 720,
                                    SDL_WINDOW_OPENGL);
    if(app->window == NULL){
        printf("%s", SDL_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if(app->gl_context == NULL){
        printf("%s", SDL_GetError());
        return;
    }

    init_opengl();
    shape_window(1280, 720);

    init_scene(&(app->scene));

    app->is_running = 1;
    app->uptime = (double)SDL_GetTicks() / 1000;
}

void event_handler(App* app) {
    SDL_Event event;

    static int is_mouse_down = 0;
    
    static int x;
    static int y;    
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_MOUSEWHEEL:
            calculate_zoom(&app->scene.camera, event.wheel.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = 1;
            break;
        case SDL_MOUSEMOTION:
            if(is_mouse_down) {
                //SDL_GetMouseState(&x, &y); <-This shit don't work, I genuinely don't understand what's up with it, every time I try to use it, it freaks out

                y = event.motion.yrel; // relative mouse motion my beloved <3
                x = event.motion.xrel; //
                
                set_pitch(&app->scene.camera, y);
                calculate_angle_around_player(&app->scene.camera, x);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = 0;
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                app->is_running = 0;
                break;
            case SDLK_f:
                app->is_windowed = !app->is_windowed;
                SDL_SetWindowFullscreen(app->window, app->is_windowed ? SDL_TRUE : SDL_FALSE);
                break;
            default:
                break;
            }
            break;         
        case SDL_QUIT:
            app->is_running = 0;
            break;
        default:
            break;
        }
    }
}

void movement(App* app) {
    move(&(app->scene.player), get_current_time(app));
    move_camera(&app->scene.camera, &app->scene.player);
}


double get_current_time(App* app) {
    float current_time = (double)SDL_GetTicks() / 1000;
    float delta = current_time - app->uptime;
    app->uptime += delta;
    return delta;

}

void modular_framerate(App* app) {

    Uint32 frameTime = (Uint32)get_current_time(app);
    if(frameTime < 16) {
        SDL_Delay(16 - frameTime);
    }

}

void update_application(App* app) {

    get_current_time(app);
    update_scene(&app->scene);

}

void render_application(App* app) {
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearColor(0.4f, 0.1f, 0.2f, 1.0f);

    glPushMatrix();
        render_scene(&app->scene);
    glPopMatrix();


    SDL_GL_SwapWindow(app->window);
    
}

void shape_window(GLsizei width, GLsizei height) {

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

}

void destroy_application(App* app) {

    SDL_DestroyWindow(app->window);
    SDL_GL_DeleteContext(app->gl_context);

    free_player(&app->scene.player);
    free_terrain(&app->scene.terrain);

    SDL_Quit();

}