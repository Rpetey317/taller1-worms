#include "SdlWormStateRedGrenade.h"
SdlWormStateRedGrenade::SdlWormStateRedGrenade(){}

bool SdlWormStateRedGrenade::is_at_max_animation_phase(int animation_phase) {
    return animation_phase == 6;
}


void SdlWormStateRedGrenade::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    renderer.Copy(*texture_map["RED_GRENADE"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
}

bool SdlWormStateRedGrenade::is_in_gun_state() {
    return true;
}

bool SdlWormStateRedGrenade::has_ammo(std::map<std::string, int>& gun_ammo) {
    return gun_ammo["RED_GRENADE"] != 0;
}

bool SdlWormStateRedGrenade::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    if (gun_ammo["RED_GRENADE"] == 0)
        return false;
    gun_ammo["RED_GRENADE"] = gun_ammo["RED_GRENADE"] -1;
    return true;
}
