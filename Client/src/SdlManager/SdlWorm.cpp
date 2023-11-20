#include "SdlWorm.h"

void SdlWorm::render_same() {
    texture_manager.render(worm_state, animation_phase, x_pos, y_pos, flip);
}

void SdlWorm::render_new(Rect rect) {

}

void SdlWorm::apply() {
    if (is_charging) { 
        attack_power = attack_power + 1;
        if (attack_power == 100) {
            attack_power = 100;
        }
    }
}

SdlWorm::SdlWorm(SdlWormTextureManager& texture_manager, SdlSoundManager& sound_manager) : texture_manager(texture_manager), sound_manager(sound_manager) {
    x_pos = 50;
    y_pos = 50;
    animation_phase = 0;
    flip = SDL_FLIP_NONE;
    attack_power = 0;
    worm_state = new SdlWormStateStill();
}
void SdlWorm::destroy() {
    sound_manager.destroy();
}

void SdlWorm::play_sound(std::string sound_to_play) {
    sound_manager.play_sound(sound_to_play);
}

void SdlWorm::next_animation() {
    
    animation_phase = animation_phase + 1;
    if (worm_state->is_at_max_animation_phase(animation_phase)) {
        animation_phase = 0;
    } 
    
}