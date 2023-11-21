#include "SdlWormStateFalling.h"
SdlWormStateFalling::SdlWormStateFalling(){}

bool SdlWormStateFalling::is_at_max_animation_phase(int animation_phase) {
    return animation_phase == 6;
}


void SdlWormStateFalling::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    renderer.Copy(*texture_map["FALLING"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
}

bool SdlWormStateFalling::is_in_gun_state() {
    return false;
}

bool SdlWormStateFalling::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    return false;
}

