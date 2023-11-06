#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "../../../Common/queue.h"

class SdlManager {

public:
    SdlManager(Queue<int>& commands, Queue<float>& positions);
    void run();

private:
    // WIP, deberia ser alguna clase comando
    Queue<int>& commands;     // alguien me deberia patear esto
    Queue<float>& positions;  // posiciones para ir actualizando
    bool event_handler();
    bool main_loop();
    void update_screen();
};
