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

void SdlWormStateAirStrike::render_ammo(Renderer& renderer, int ammount_of_ammo, int camera_x, int camera_y) {
    Rect dest;
    Color color;
    color.SetBlue(255);
    color.SetGreen(153);
    color.SetRed(153);
    for (int i = 0; i < ammount_of_ammo; i++) {
        dest.SetX(camera_x + i*AMMO_RENDER_SEPARATION);
        dest.SetY(camera_y);
        dest.SetW(AMMO_RENDER_WIDTH);
        dest.SetH(AMMO_RENDER_HEIGHT);
        renderer.SetDrawColor(color);
        renderer.FillRect(dest);
    }
}

std::string SdlWormStateAirStrike::get_name() {
    return "AIR_STRIKE";
}

int SdlWormStateAirStrike::projectile_id() {
    return AIR_STRIKE;
}

void SdlWormStateAirStrike::play_sound(SdlSoundManager& sound_manager) {
    sound_manager.play_sound("AIR_STRIKE_THROWING_SOUND");
}
