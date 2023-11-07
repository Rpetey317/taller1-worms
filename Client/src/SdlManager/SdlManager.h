#include <iostream>
#include <string>
#include <vector>

#include "../../../Common/queue.h"

#include "SdlMap.h"
#include "SdlWorm.h"
using namespace SDL2pp;  // NOLINT
class SdlManager {

public:
    SdlManager(Queue<int>& commands, Queue<std::vector<float>>& positions);
    void run();

private:
    // WIP, deberia ser alguna clase comando
    Queue<int>& commands;                  // alguien me deberia patear esto
    Queue<std::vector<float>>& positions;  // posiciones para ir actualizando

    bool event_handler();
    bool main_loop(Renderer& renderer, SdlWorm& worm, SdlMap& map);
    void update_screen(Renderer& renderer, SdlWorm& worm, SdlMap& map);
};
