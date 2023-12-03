#include "SdlWormStateRedGrenade.h"
SdlWormStateRedGrenade::SdlWormStateRedGrenade(){}

bool SdlWormStateRedGrenade::is_at_max_animation_phase(int animation_phase) {
    if (just_choosen) {
        bool result = (animation_phase == 6);
        if (result)
            just_choosen = false;
        return result;
    }
    return animation_phase == 6;
}


void SdlWormStateRedGrenade::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    
    if (just_choosen) {
        renderer.Copy(*texture_map["CHOOSING_RED_GRENADE"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    } else {
        renderer.Copy(*texture_map["RED_GRENADE"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    }
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

void SdlWormStateRedGrenade::render_ammo(Renderer& renderer, int ammount_of_ammo, int camera_x, int camera_y) {
    Rect dest;
    Color color;
    color.SetBlue(51);
    color.SetGreen(51);
    color.SetRed(255);
    for (int i = 0; i < ammount_of_ammo; i++) {
        dest.SetX(camera_x + i*AMMO_RENDER_SEPARATION);
        dest.SetY(camera_y);
        dest.SetW(AMMO_RENDER_WIDTH);
        dest.SetH(AMMO_RENDER_HEIGHT);
        renderer.SetDrawColor(color);
        renderer.FillRect(dest);
    }
}

std::string SdlWormStateRedGrenade::get_name() {
    return "RED_GRENADE";
}
