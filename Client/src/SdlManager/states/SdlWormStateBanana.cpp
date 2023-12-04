#include "SdlWormStateBanana.h"
SdlWormStateBanana::SdlWormStateBanana(){}

bool SdlWormStateBanana::is_at_max_animation_phase(int animation_phase) {
    if (just_choosen) {
        bool result = (animation_phase == 6);
        if (result)
            just_choosen = false;
        return result;
    }
    return animation_phase == 6;
}


void SdlWormStateBanana::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    if (just_choosen) {
        renderer.Copy(*texture_map["CHOOSING_BANANA"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    } else {
        renderer.Copy(*texture_map["BANANA"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    }
}

bool SdlWormStateBanana::is_in_gun_state() {
    return true;
}

bool SdlWormStateBanana::has_ammo(std::map<std::string, int>& gun_ammo) {
    return gun_ammo["BANANA"] != 0;
}

bool SdlWormStateBanana::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    if (!has_ammo(gun_ammo))
        return false;
    gun_ammo["BANANA"] = gun_ammo["BANANA"] -1;
    return true;
}

void SdlWormStateBanana::render_ammo(Renderer& renderer, int ammount_of_ammo, int position_x, int position_y) {
    Rect dest;
    Color color;
    color.SetBlue(100);
    color.SetGreen(255);
    color.SetRed(255);
    for (int i = 0; i < ammount_of_ammo; i++) {
        dest.SetX(position_x + i*AMMO_RENDER_SEPARATION);
        dest.SetY(position_y);
        dest.SetW(AMMO_RENDER_WIDTH);
        dest.SetH(AMMO_RENDER_HEIGHT);
        renderer.SetDrawColor(color);
        renderer.FillRect(dest);
    }
}

std::string SdlWormStateBanana::get_name() {
    return "BANANA";
}


int SdlWormStateBanana::projectile_id() {
    return 0x0007;
}

void SdlWormStateBanana::play_sound(SdlSoundManager& sound_manager) {
    
}
