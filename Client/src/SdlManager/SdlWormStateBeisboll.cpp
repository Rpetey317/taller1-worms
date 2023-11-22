#include "SdlWormStateBeisboll.h"
SdlWormStateBeisboll::SdlWormStateBeisboll(){}

bool SdlWormStateBeisboll::is_at_max_animation_phase(int animation_phase) {
    return animation_phase == 6;
}


void SdlWormStateBeisboll::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    renderer.Copy(*texture_map["BEISBOLL"], Rect(0, 60 * animation_phase, 58, 58), dest, 0, NullOpt, flip);
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
