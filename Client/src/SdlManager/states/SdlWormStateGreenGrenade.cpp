#include "SdlWormStateGreenGrenade.h"
SdlWormStateGreenGrenade::SdlWormStateGreenGrenade(){}

bool SdlWormStateGreenGrenade::is_at_max_animation_phase(int animation_phase) {
    if (just_choosen) {
        bool result = (animation_phase == 6);
        if (result)
            just_choosen = false;
        return result;
    }
    return animation_phase == 6;
}


void SdlWormStateGreenGrenade::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    if (just_choosen) {
        renderer.Copy(*texture_map["CHOOSING_GREEN_GRENADE"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    } else {
        renderer.Copy(*texture_map["GREEN_GRENADE"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    }
}


bool SdlWormStateGreenGrenade::is_in_gun_state() {
    return true;
}
bool SdlWormStateGreenGrenade::has_ammo(std::map<std::string, int>& gun_ammo) {
    return gun_ammo["GREEN_GRENADE"] != 0;
}

bool SdlWormStateGreenGrenade::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    if (!has_ammo(gun_ammo))
        return false;
    
    gun_ammo["GREEN_GRENADE"] = gun_ammo["GREEN_GRENADE"] -1;
    
    return true;
}


std::string SdlWormStateGreenGrenade::get_name() {
    return "GREEN_GRENADE";
}
int SdlWormStateGreenGrenade::projectile_id() {
    return 0x0005;
}
