#include "SdlWormStateBeisboll.h"
SdlWormStateBeisboll::SdlWormStateBeisboll(){}

bool SdlWormStateBeisboll::is_at_max_animation_phase(int animation_phase) {
    if (just_choosen) {
        bool result = (animation_phase == 6);
        if (result)
            just_choosen = false;
        return result;
    }
    if (is_animation_playing) {
        bool result = (animation_phase == 3);
        if (result)
            is_animation_playing = false;
        return result;
    }

    return animation_phase == 6;
}


void SdlWormStateBeisboll::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    
    
    if (is_animation_playing) {
        renderer.Copy(*texture_map["BEISBOLL_ATTACK"], Rect(0, 60 * animation_phase, 58, 58), dest, 0, NullOpt, flip);
    } else if (just_choosen) {
        renderer.Copy(*texture_map["CHOOSING_BEISBOLL"], Rect(0, 60 * animation_phase, 58, 58), dest, 0, NullOpt, flip);

    } else {
        renderer.Copy(*texture_map["BEISBOLL"], Rect(0, 60 * animation_phase, 58, 58), dest, 0, NullOpt, flip);
    }

}

bool SdlWormStateBeisboll::is_in_gun_state() {
    return true;
}

bool SdlWormStateBeisboll::has_ammo(std::map<std::string, int>& gun_ammo) {
    return true;
}

bool SdlWormStateBeisboll::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    return true;
}

int SdlWormStateBeisboll::projectile_id() {
    return BASEBALL_BAT;
}