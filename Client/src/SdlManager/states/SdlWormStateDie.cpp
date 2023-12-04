#include "SdlWormStateDie.h"

SdlWormStateDie::SdlWormStateDie(){}

bool SdlWormStateDie::is_at_max_animation_phase(int animation_phase) {
    if (is_animation_playing) {
        bool result = (animation_phase == 25);
        if (result)
            is_animation_playing = false;
        return result;
    }
    return animation_phase >= 0;
}


void SdlWormStateDie::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    if (is_animation_playing) {
        renderer.Copy(*texture_map["DIE"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    }
}

bool SdlWormStateDie::is_in_gun_state() {
    return false;
}

bool SdlWormStateDie::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    return false;
}
bool SdlWormStateDie::has_ammo(std::map<std::string, int>& gun_ammo) {
    return false;
}
