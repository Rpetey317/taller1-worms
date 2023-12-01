#include "SdlWormStateBanana.h"
SdlWormStateBanana::SdlWormStateBanana(){}

bool SdlWormStateBanana::is_at_max_animation_phase(int animation_phase) {
    if (just_choosen) {
        bool result = (animation_phase == 6);
        if (result)
            just_choosen = false;
        return result;
    }
    return animation_phase == 6;
}


void SdlWormStateBanana::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    if (just_choosen) {
        renderer.Copy(*texture_map["CHOOSING_BANANA"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    } else {
        renderer.Copy(*texture_map["BANANA"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    }
}

bool SdlWormStateBanana::is_in_gun_state() {
    return true;
}

bool SdlWormStateBanana::has_ammo(std::map<std::string, int>& gun_ammo) {
    return true;
}

bool SdlWormStateBanana::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    return true;
}
