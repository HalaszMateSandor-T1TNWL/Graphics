#include "Utils/application.h"

void init_application(App* app) {
    int error_code;
    app->width = 1280;
    app->height = 720;

    app->is_running = 0;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if(error_code != 0){
        printf("%s", SDL_GetError());
        return;
    } else{
        printf("Successfully initialized everything!\nReady for work~\n");
    }

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    app->window = SDL_CreateWindow("Character Movement",
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                    app->width, app->height,
                                    SDL_WINDOW_OPENGL);
    if(app->window == NULL){
        printf("%s", SDL_GetError());
        return;
    } else{
        printf("Window successfully created!\n");
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if(app->gl_context == NULL){
        printf("%s", SDL_GetError());
        return;
    } else{
        printf("OpenGL Context successfully established!\n");
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
    move(&app->scene.player, get_current_time(app));
    update_bounding_box(&app->scene.player.box, app->scene.player.position, app->scene.player.size);

    for (int i = 0; i < 4; i++) {
        update_bounding_box(&app->scene.objects[i].box, app->scene.objects[i].position, app->scene.objects[i].size);
        if (check_collision(&app->scene.player.box, &app->scene.objects[i].box)) {
            handle_collision(&app->scene.objects[i], &app->scene.player);
        }
    }
    if(app->scene.player.position.y < TERRAIN_HEIGHT) {
        app->scene.player.position.y = TERRAIN_HEIGHT;
        app->scene.player.is_in_air = false;
        app->scene.player.jumped = 0;
        update_bounding_box(&app->scene.player.box, app->scene.player.position, app->scene.player.size);
    }
    move_camera(&app->scene.camera, &app->scene.player);
}


float get_current_time(App* app) {
    float current_time = (float)SDL_GetTicks() / 1000;
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
    update_scene(&app->scene, get_current_time(app));
}

void render_application(App* app) {
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render_scene(&app->scene);

    GLenum error = glGetError();
    while(error != GL_NO_ERROR){
        fprintf(stderr, "OpenGL Error: %d\n", error);
        error = glGetError();
    }

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

    free_entity(&app->scene.player);
    free_entity(&app->scene.objects[0]);
    free_entity(&app->scene.objects[1]);
    free_entity(&app->scene.objects[2]);
    free_terrain(&app->scene.terrain);
    free_skybox(&app->scene);

    SDL_Quit();

}