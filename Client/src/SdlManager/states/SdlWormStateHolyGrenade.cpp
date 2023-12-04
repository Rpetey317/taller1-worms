#include "SdlWormStateHolyGrenade.h"
SdlWormStateHolyGrenade::SdlWormStateHolyGrenade(){}

bool SdlWormStateHolyGrenade::is_at_max_animation_phase(int animation_phase) {
    if (just_choosen) {
        bool result = (animation_phase == 6);
        if (result)
            just_choosen = false;
        return result;
    }
    return animation_phase == 6;
}


void SdlWormStateHolyGrenade::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    
    if (just_choosen) {
        renderer.Copy(*texture_map["CHOOSING_HOLY_GRENADE"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);        
    } else {
        renderer.Copy(*texture_map["HOLY_GRENADE"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    }
}

bool SdlWormStateHolyGrenade::is_in_gun_state() {
    return true;
}

bool SdlWormStateHolyGrenade::has_ammo(std::map<std::string, int>& gun_ammo) {
    return gun_ammo["HOLY_GRENADE"] != 0;
}

bool SdlWormStateHolyGrenade::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    if (!has_ammo(gun_ammo))
        return false;
    
    gun_ammo["HOLY_GRENADE"] = gun_ammo["HOLY_GRENADE"] -1;
    
    return true;
}

void SdlWormStateHolyGrenade::render_ammo(Renderer& renderer, int ammount_of_ammo, int camera_x, int camera_y) {
    Rect dest;
    Color color;
    color.SetBlue(0);
    color.SetGreen(204);
    color.SetRed(204);
    for (int i = 0; i < ammount_of_ammo; i++) {
        dest.SetX(camera_x + i*AMMO_RENDER_SEPARATION);
        dest.SetY(camera_y);
        dest.SetW(AMMO_RENDER_WIDTH);
        dest.SetH(AMMO_RENDER_HEIGHT);
        renderer.SetDrawColor(color);
        renderer.FillRect(dest);
    }
}

std::string SdlWormStateHolyGrenade::get_name() {
    return "HOLY_GRENADE";
}

int SdlWormStateHolyGrenade::projectile_id() {
    return 0x0008;
}