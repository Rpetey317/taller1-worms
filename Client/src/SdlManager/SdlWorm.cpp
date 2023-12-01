#include "SdlWorm.h"
#include <tgmath.h>


void SdlWorm::set_health(int new_health) {
    
    if (new_health >= initial_health) {
        health = initial_health;
        return;
    }
    health = new_health;

}

void SdlWorm::recharge_ammo() {
    std::cout << "RECARGANDO BALAS" << std::endl;
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
}

void SdlWorm::render_same() {
    texture_manager.render(worm_state, animation_phase, x_pos, y_pos, flip);
    health_bar.SetX(x_pos);
    health_bar.SetY(y_pos - 10);
    health_bar.SetW(health/2);

    health_bar_delim.SetX(x_pos -1);
    health_bar_delim.SetY(y_pos - 11);
    health_bar_delim.SetW((health/2) +2);
    renderer.SetDrawColor(delim_color);
    renderer.DrawRect(health_bar_delim);
    renderer.SetDrawColor(color);
    renderer.FillRect(health_bar);

}

void SdlWorm::render_new(Vect2D position) {
    x_pos = position.x;
    y_pos = position.y;
    if (is_animation_playing) {
        texture_manager.render(worm_state, animation_phase, position.x, position.y, flip);
    } else {
        texture_manager.render(worm_state, animation_phase, position.x, position.y, flip);
    }
    health_bar.SetX(x_pos);
    health_bar.SetY(y_pos - 10);
    health_bar.SetW(health/2);

    health_bar_delim.SetX(x_pos -1);
    health_bar_delim.SetY(y_pos - 11);
    health_bar_delim.SetW((health/2)+2);
    renderer.SetDrawColor(delim_color);
    renderer.DrawRect(health_bar_delim);
    renderer.SetDrawColor(color);
    renderer.FillRect(health_bar);
    
}

void SdlWorm::apply() {
    if (is_charging) { 
        attack_power = attack_power + 1;
        if (attack_power == 100) {
            attack_power = 100;
        }
    }
}

void SdlWorm::set_color() {
    delim_color.SetBlue(0);
    delim_color.SetGreen(102);
    delim_color.SetRed(204);
    switch (player_id)
    {
    case 0:
        color.SetBlue(255);
        color.SetGreen(0);
        color.SetRed(0);
        break;
    case 1:
        color.SetBlue(0);
        color.SetGreen(255);
        color.SetRed(0);
        break;
    case 2:
        color.SetBlue(0);
        color.SetGreen(0);
        color.SetRed(255);
        break;
    case 3:
        color.SetBlue(255);
        color.SetGreen(255);
        color.SetRed(0);
        break;
    case 4:
        color.SetBlue(255);
        color.SetGreen(0);
        color.SetRed(255);
        break;
    case 5:
        color.SetBlue(0);
        color.SetGreen(255);
        color.SetRed(255);
        break;
    case 6:
        color.SetBlue(192);
        color.SetGreen(192);
        color.SetRed(128);
        break;
    case 7:
        color.SetBlue(128);
        color.SetGreen(192);
        color.SetRed(192);
        break;
    case 8:
        color.SetBlue(192);
        color.SetGreen(128);
        color.SetRed(192);
        break;
        
    default:
        color.SetBlue(128);
        color.SetGreen(128);
        color.SetRed(192);
        break;
    }

}

SdlWorm::SdlWorm(Renderer& renderer, SdlWormTextureManager& texture_manager, SdlSoundManager& sound_manager, int x_pos, int y_pos, int worm_id, int player_id, int health) : renderer(renderer), texture_manager(texture_manager), sound_manager(sound_manager) {
    this->worm_id = worm_id;
    this->player_id = player_id;
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    animation_phase = 0;
    flip = SDL_FLIP_NONE;
    attack_power = 0;
    is_animation_playing = false;
    this->health = health;
    initial_health = health;
    health_bar.SetH(10);
    health_bar.SetW(health/2);
    health_bar_delim.SetH(12);
    health_bar_delim.SetW((health/2) + 2);
    set_color();

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

    

    recharge_ammo();

    worm_state = worm_states["STILL"];
}
bool SdlWorm::has_ammo() {
    bool result = worm_state->has_ammo(gun_ammo);
    std::cout << result << std::endl;
    return result;
}
void SdlWorm::play_animation() {
    is_animation_playing = true;
    animation_phase = 0;
    worm_state->play_animation();
}
bool SdlWorm::reduce_ammo() { return worm_state->reduce_ammo(gun_ammo); }

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

bool SdlWorm::next_animation() {


    if (is_animation_playing) {
        animation_phase = animation_phase + 1;
        if (worm_state->is_at_max_animation_phase(animation_phase)) {
            animation_phase = 0;
            is_animation_playing = false;
        } 
        return true;
    }
    if (worm_state->is_in_gun_state() && !worm_state->just_choosen) {
        if (angle >= 0) {
            int animation_angle = angle + 90;
            animation_phase = round(animation_angle / 6);
        } else {
            int animation_angle = angle + 90;
            animation_phase = round(animation_angle/6);
        }
        return false;
    }
        
    animation_phase = animation_phase + 1;
    if (worm_state->is_at_max_animation_phase(animation_phase)) {
        animation_phase = 0;
    } 
    
    return false;
}

void SdlWorm::change_state(std::string state) {
    
    if (worm_state == worm_states[state]) 
        return;

    animation_phase = 0;
    worm_state = worm_states[state];
    std::cout << "CAMBIO MI ESTADO" << std::endl;
    worm_state->play_choosen_animation();
    angle = 0;
    attack_power = 0;
}

bool SdlWorm::is_in_gun_state() {
    return worm_state->is_in_gun_state();
}
