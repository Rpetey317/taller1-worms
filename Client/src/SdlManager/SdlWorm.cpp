#include "SdlWorm.h"
#include <tgmath.h>
void SdlWorm::render_same() {
    texture_manager.render(worm_state, animation_phase, x_pos, y_pos, flip);
}

void SdlWorm::render_new(Vect2D position) {
    x_pos = position.x;
    y_pos = position.y;
    std::cout << position.x << " " << position.y << std::endl;
    texture_manager.render(worm_state, animation_phase, position.x, position.y, flip);
}

void SdlWorm::apply() {
    if (is_charging) { 
        attack_power = attack_power + 1;
        if (attack_power == 100) {
            attack_power = 100;
        }
    }
}

SdlWorm::SdlWorm(SdlWormTextureManager& texture_manager, SdlSoundManager& sound_manager, int id) : texture_manager(texture_manager), sound_manager(sound_manager) {
    this->id = id;
    x_pos = 50;
    y_pos = 50;
    animation_phase = 0;
    flip = SDL_FLIP_NONE;
    attack_power = 0;

    worm_states["AIR_STRIKE"] = new SdlWormStateAirStrike();
    worm_states["BANANA"] = new SdlWormStateBanana();
    worm_states["BAZOOKA"] = new SdlWormStateBazooka();
    worm_states["BEISBOLL"] = new SdlWormStateBeisboll();
    worm_states["DYNAMITE"] = new SdlWormStateDynamite();
    worm_states["FALLING"] = new SdlWormStateFalling();
    worm_states["GREEN_GRENADE"] = new SdlWormStateGreenGrenade();
    worm_states["HOLY_GRENADE"] = new SdlWormStateHolyGrenade();
    worm_states["MORTAR"] = new SdlWormStateMortar();
    worm_states["RED_GRENADE"] = new SdlWormStateRedGrenade();
    worm_states["STILL"] = new SdlWormStateStill();
    worm_states["TELEPORT"] = new SdlWormStateTeleport();
    worm_states["WALK"] = new SdlWormStateWalk();

    gun_ammo["BANANA"] = -1;
    gun_ammo["BAZOOKA"] = -1;
    gun_ammo["BEISBOLL"] = -1;
    gun_ammo["TELEPORT"] = -1;

    gun_ammo["MORTAR"] = 10;
    gun_ammo["GREEN_GRENADE"] = 5;
    gun_ammo["HOLY_GRENADE"] = 2;
    gun_ammo["DYNAMITE"] = 5;
    gun_ammo["RED_GRENADE"] = 10;
    gun_ammo["AIR_STRIKE"] = 2;

    worm_state = worm_states["STILL"];
}
bool SdlWorm::has_ammo() {
    bool result = worm_state->has_ammo(gun_ammo);
    std::cout << result << std::endl;
    return result;
}
bool SdlWorm::reduce_ammo() {
    return worm_state->reduce_ammo(gun_ammo);
}

void SdlWorm::destroy() {
    //sound_manager.destroy();
    //for (auto state : worm_states) {
    //    delete state.second;
    //}
}

void SdlWorm::play_sound(std::string sound_to_play) {
    sound_manager.play_sound(sound_to_play);
}

void SdlWorm::change_angle(int angle) {
    this->angle = this->angle + angle;
    if (this->angle >= 90) 
        this->angle = 90;
    else if (this->angle < -90) 
        this->angle = -90;
}

void SdlWorm::next_animation() {//30 animaciones de angulos
    if (worm_state->is_in_gun_state()) {
        if (angle >= 0) {
            int animation_angle = angle + 90;
            animation_phase = round(animation_angle / 6);
        } else {
            int animation_angle = angle + 90;
            animation_phase = round(animation_angle/6);
        }
        return;
    }
        
    animation_phase = animation_phase + 1;
    if (worm_state->is_at_max_animation_phase(animation_phase)) {
        animation_phase = 0;
    } 
    
}

void SdlWorm::change_state(std::string state) {
    
    if (worm_state == worm_states[state]) 
        return;

    animation_phase = 0;
    worm_state = worm_states[state];
    angle = 0;
    attack_power = 0;
}

bool SdlWorm::is_in_gun_state() {
    return worm_state->is_in_gun_state();
}
