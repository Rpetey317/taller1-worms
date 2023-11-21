#include "SdlWormStateHolyGrenade.h"
SdlWormStateHolyGrenade::SdlWormStateHolyGrenade(){}

bool SdlWormStateHolyGrenade::is_at_max_animation_phase(int animation_phase) {
    return animation_phase == 6;
}


void SdlWormStateHolyGrenade::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    renderer.Copy(*texture_map["HOLY_GRENADE"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
}

bool SdlWormStateHolyGrenade::is_in_gun_state() {
    return true;
}
