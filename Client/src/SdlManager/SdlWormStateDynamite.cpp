#include "SdlWormStateDynamite.h"
SdlWormStateDynamite::SdlWormStateDynamite(){}

bool SdlWormStateDynamite::is_at_max_animation_phase(int animation_phase) {
    return animation_phase == 3;
}


void SdlWormStateDynamite::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    renderer.Copy(*texture_map["DYNAMITE"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
}


bool SdlWormStateDynamite::is_in_gun_state() {
    return false;
}
