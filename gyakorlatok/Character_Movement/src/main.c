#include "../include/Utils/application.h"

int main(int argc, char* argv[]){
    App app;

    init_application(&app);

    while(app.is_running){
        update_application(&app);
        event_handler(&app);
    }

    destroy_application(&app);
    
    return 0;
}