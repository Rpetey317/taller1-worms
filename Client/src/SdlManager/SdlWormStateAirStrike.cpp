#include "SdlWormStateAirStrike.h"
SdlWormStateAirStrike::SdlWormStateAirStrike(){}

bool SdlWormStateAirStrike::is_at_max_animation_phase(int animation_phase) {
    return animation_phase == 3;
}


void SdlWormStateAirStrike::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    renderer.Copy(*texture_map["AIR_STRIKE"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
}

bool SdlWormStateAirStrike::is_in_gun_state() {
    return false;
}


bool SdlWormStateAirStrike::has_ammo(std::map<std::string, int>& gun_ammo) {
    return gun_ammo["AIR_STRIKE"] != 0;
}

bool SdlWormStateAirStrike::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    if (!has_ammo(gun_ammo))
        return false;

    gun_ammo["AIR_STRIKE"] = gun_ammo["AIR_STRIKE"] -1;
    return true;
}

