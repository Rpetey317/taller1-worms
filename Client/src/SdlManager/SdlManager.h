#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
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
    SdlManager(Queue<std::shared_ptr<Action>>& outgoing, Queue<std::shared_ptr<Event>>& ingoing, int id_of_player);
    void run(std::string background_type, std::string selected_map);  //este background_type lo deberia recibir para saber que cargar, quiza vienen por el server (?

private:

    Queue<std::shared_ptr<Action>>& outgoing;                
    Queue<std::shared_ptr<Event>>& ingoing;  
    std::map<int, SdlWorm*> worms;
    int id_of_player_turn;
    int id_worm_turn;
    int id_of_player;
    void cheat_set_life_of_all_worms_to(int new_health);
    bool event_handler();
    bool main_loop(Renderer& renderer, SdlMap& map, SdlSoundManager& sound_manager, SdlWormTextureManager& worm_texture_manager);
    void update_screen(Renderer& renderer, SdlMap& map, SdlSoundManager& sound_manager, SdlWormTextureManager& worm_texture_manager);
};
