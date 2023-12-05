#include "SdlWormStateTeleport.h"
SdlWormStateTeleport::SdlWormStateTeleport(){}

bool SdlWormStateTeleport::is_at_max_animation_phase(int animation_phase) {
    if (is_animation_playing) {
        bool result = (animation_phase == 50);
        if (result)
            is_animation_playing = false;
        return result;
    }
    return animation_phase == 3;
}


void SdlWormStateTeleport::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    
    if (is_animation_playing) {
        renderer.Copy(*texture_map["TELEPORTING"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    } else {
        renderer.Copy(*texture_map["TELEPORT"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
    }
}

bool SdlWormStateTeleport::is_in_gun_state() {
    return false;
}

bool SdlWormStateTeleport::reduce_ammo(std::map<std::string, int>& gun_ammo) {
    return true;
}

bool SdlWormStateTeleport::has_ammo(std::map<std::string, int>& gun_ammo) {
    return true;
}


int SdlWormStateTeleport::projectile_id() {
    return TELEPORT;
}

void SdlWormStateTeleport::play_sound(SdlSoundManager& sound_manager) {
    sound_manager.play_sound("TELEPORT_SOUND");
}
