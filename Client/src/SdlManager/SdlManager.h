#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <exception>
#include <string>
#include <unistd.h>

#include <SDL2pp/SDL2pp.hh>
#include "SdlWorm.h"
#include "SdlMap.h"
#include "SdlWormState.h"
#include "SdlWormStateStill.h"
#include "SdlWormStateBazooka.h"
#include "SdlWormStateWalk.h"
#include "../../../Common/queue.h"
#include "../Event/EventHeaders.h"
#include "../Action/ActionHeaders.h"
using namespace SDL2pp;  // NOLINT
class SdlManager {

public:
    SdlManager(Queue<Action*>& outgoing, Queue<Event*>& ingoing, int id_of_player);
    void run(std::string background_type, std::string selected_map);  //este background_type lo deberia recibir para saber que cargar, quiza vienen por el server (?

private:
    // WIP, deberia ser alguna clase comando
    Queue<Action*>& outgoing;                // alguien me deberia patear esto
    Queue<Event*>& ingoing;  // posiciones para ir actualizando
    std::map<int, SdlWorm*> worms;
    int id_of_player_turn;
    int id_of_player;

    bool event_handler();
    bool main_loop(Renderer& renderer, SdlMap& map);
    void update_screen(Renderer& renderer, SdlMap& map);
};
