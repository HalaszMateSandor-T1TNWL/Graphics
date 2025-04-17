#include "Utils/application.h"

void init_application(App* app) {
    int error_code;

    app->is_running = 0;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if(error_code != 0){
        printf("%s", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow("Character Movement",
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                    1080,720,
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

    while(SDL_PollEvent(&event)) {
        switch (event.type) {
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
}

double get_current_time(App* app) {
    float current_time = (double)SDL_GetTicks() / 1000;
    float delta = current_time - app->uptime;
    app->uptime += delta;
    return delta;
}

void modular_framerate(App* app) {
    Uint32 frameTime = (Uint32)get_current_time(app);
    if(frameTime < 16){
        SDL_Delay(16 - frameTime);
    }
}

void update_application(App* app) {
    get_current_time(app);
    update_scene(&(app->scene));
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
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if(ratio > VIEWPORT_RATIO){
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    } else{
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void destroy_application(App* app) {

    SDL_DestroyWindow(app->window);
    SDL_GL_DeleteContext(app->gl_context);

    free_model(&app->scene.player.player_model);

    SDL_Quit();
}