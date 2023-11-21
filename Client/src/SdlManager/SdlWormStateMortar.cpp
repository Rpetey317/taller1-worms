#include "SdlWormStateMortar.h"
SdlWormStateMortar::SdlWormStateMortar(){}

bool SdlWormStateMortar::is_at_max_animation_phase(int animation_phase) {
    return animation_phase == 6;
}


void SdlWormStateMortar::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    renderer.Copy(*texture_map["MORTAR"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
}

bool SdlWormStateMortar::is_in_gun_state() {
    return true;
}

bool SdlWormStateMortar::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    gun_ammo["MORTAR"] = gun_ammo["MORTAR"] -1;
    if (gun_ammo["MORTAR"] == 0)
        return true;
    return false;
}
