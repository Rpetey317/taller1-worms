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

bool SdlWormStateDynamite::has_ammo(std::map<std::string, int>& gun_ammo) {
    return gun_ammo["DYNAMITE"] != 0;
}


bool SdlWormStateDynamite::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    
    if (!has_ammo(gun_ammo))
        return false;
    gun_ammo["DYNAMITE"] = gun_ammo["DYNAMITE"] -1;
    return true;
}

void SdlWormStateDynamite::render_ammo(Renderer& renderer, int ammount_of_ammo, int position_x, int position_y) {
    Rect dest;
    Color color;
    color.SetBlue(0);
    color.SetGreen(0);
    color.SetRed(153);
    for (int i = 0; i < ammount_of_ammo; i++) {
        dest.SetX(position_x + i*AMMO_RENDER_SEPARATION);
        dest.SetY(position_y);
        dest.SetW(AMMO_RENDER_WIDTH);
        dest.SetH(AMMO_RENDER_HEIGHT);
        renderer.SetDrawColor(color);
        renderer.FillRect(dest);
    }
}

std::string SdlWormStateDynamite::get_name() {
    return "DYNAMITE";
}
