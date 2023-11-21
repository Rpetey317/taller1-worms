#include "SdlWormStateBazooka.h"
SdlWormStateBazooka::SdlWormStateBazooka(){}

bool SdlWormStateBazooka::is_at_max_animation_phase(int animation_phase) {
    return animation_phase == 6;
}


void SdlWormStateBazooka::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    renderer.Copy(*texture_map["BAZOOKA"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
}

bool SdlWormStateBazooka::is_in_gun_state() {
    return true;
}

bool SdlWormStateBazooka::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    return false;
}