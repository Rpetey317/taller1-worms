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
#include "SdlCamera.h"
#include "SdlWorm.h"
#include "SdlMap.h"
#include "texture_sound_manager/SdlProjectilesTextureManager.h"
#include "texture_sound_manager/SdlSoundManager.h"
#include "../../../Common/Vect2D.h"
#include "projectiles/common_projectiles.h"
#include "../../../Common/queue.h"
#include "../Event/EventHeaders.h"
#include "../Action/ActionHeaders.h"
using namespace SDL2pp;  // NOLINT
class SdlManager {

public:
    SdlManager(Queue<std::shared_ptr<Action>>& outgoing, Queue<std::shared_ptr<Event>>& ingoing);
    void run(std::string selected_map);

private:

    Queue<std::shared_ptr<Action>>& outgoing;                
    Queue<std::shared_ptr<Event>>& ingoing;  
    std::map<int, SdlWorm*> worms;
    std::map<std::string, SdlProjectile*> projectiles;
    int id_of_player_turn;
    int id_worm_turn;
    bool is_animation_playing;
    SdlCamera camera;
    bool is_moving_camera;
    std::string last_projectile_used;
    bool is_projectile_flying;
    int timer;
    SdlResizableRect timer_rect;
    
    void init_projectiles(SdlSoundManager& sound_manager, SdlProjectilesTextureManager& projectiles_texture_manager, SdlCamera& camera);
    void cheat_set_life_of_all_worms_to(int new_health);
    bool event_handler();
    bool main_loop(Renderer& renderer, SdlMap& map, SdlSoundManager& sound_manager, SdlWormTextureManager& worm_texture_manager);
    void update_screen(Renderer& renderer, SdlMap& map, SdlSoundManager& sound_manager, SdlWormTextureManager& worm_texture_manager);
};
