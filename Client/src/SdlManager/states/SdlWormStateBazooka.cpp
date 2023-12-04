#include "SdlWormStateBazooka.h"
SdlWormStateBazooka::SdlWormStateBazooka(){}

bool SdlWormStateBazooka::is_at_max_animation_phase(int animation_phase) {
    if (just_choosen) {
        bool result = (animation_phase == 6);
        if (result)
            just_choosen = false;
        return result;
    }
    return animation_phase == 6;
}


void SdlWormStateBazooka::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    
    if (just_choosen) {
        renderer.Copy(*texture_map["CHOOSING_BAZOOKA"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    } else {
        renderer.Copy(*texture_map["BAZOOKA"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    }

}

bool SdlWormStateBazooka::is_in_gun_state() {
    return true;
}

bool SdlWormStateBazooka::has_ammo(std::map<std::string, int>& gun_ammo) {
    return true;
}

bool SdlWormStateBazooka::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    return true;
}
int SdlWormStateBazooka::projectile_id() {
    return BAZOOKA;
}

void SdlWormStateBazooka::play_sound(SdlSoundManager& sound_manager) {
    sound_manager.play_sound("BAZOOKA_MORTAR_THROWING_SOUND");
}
