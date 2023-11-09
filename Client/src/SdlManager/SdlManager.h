#include <iostream>
#include <string>
#include <vector>

#include "../../../Common/queue.h"

#include "SdlMap.h"
#include "SdlWorm.h"
using namespace SDL2pp;  // NOLINT
class SdlManager {

public:
    SdlManager(Queue<int>& commands, Queue<std::vector<int>>& positions);
    void run();

private:
    // WIP, deberia ser alguna clase comando
    Queue<int>& commands;                // alguien me deberia patear esto
    Queue<std::vector<int>>& positions;  // posiciones para ir actualizando

    bool event_handler(SdlWorm& worm, SDL_AudioDeviceID device, uint8_t* waveStart,
                       uint32_t waveLength);
    bool main_loop(Renderer& renderer, SdlWorm& worm, SdlMap& map, SDL_AudioDeviceID device,
                   uint8_t* waveStart, uint32_t waveLength);
    void update_screen(Renderer& renderer, SdlWorm& worm, SdlMap& map);
};
