#include "../include/Utils/application.h"

int main(int argc, char* argv[]){
    App app;

    init_application(&app);

    while(app.is_running){
        event_handler(&app);
        update_application(&app);
        render_application(&app);
        modular_framerate();
    }
    destroy_application(&app);
    
    return 0;
}