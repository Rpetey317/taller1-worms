#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../../../Common/queue.h"

#include "SdlMap.h"
#include "SdlWorm.h"
#include "SdlTexturesManager.h"
#include "SdlSoundManager.h"
#include "SdlWormTextureManager.h"
#include "SdlWormState.h"
#include "SdlWormStateBazooka.h"
#include "SdlWormStateWalk.h"
#include "SdlWormStateStill.h"
using namespace SDL2pp;  // NOLINT
class SdlManager {

public:
    SdlManager(Queue<int>& commands, Queue<std::vector<int>>& positions, int id_of_player);
    void run(std::string background_type, std::string selected_map);  //este background_type lo deberia recibir para saber que cargar, quiza vienen por el server (?

private:
    // WIP, deberia ser alguna clase comando
    Queue<int>& commands;                // alguien me deberia patear esto
    Queue<std::vector<int>>& positions;  // posiciones para ir actualizando
    std::map<int, SdlWorm*> worms;
    int id_of_player_turn;
    int id_of_player;

    bool event_handler();
    bool main_loop(Renderer& renderer, SdlMap& map);
    void update_screen(Renderer& renderer, SdlMap& map);
};
