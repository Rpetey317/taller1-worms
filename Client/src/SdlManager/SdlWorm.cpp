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

    gun_ammo["NULL"] = 0;
    gun_ammo["BANANA"] = weapon_config.banana.ammount_of_bullets;
    gun_ammo["BAZOOKA"] = weapon_config.bazooka.ammount_of_bullets;
    gun_ammo["BEISBOLL"] = weapon_config.beisboll.ammount_of_bullets;
    gun_ammo["TELEPORT"] = -1;

    gun_ammo["MORTAR"] = weapon_config.mortar.ammount_of_bullets;
    gun_ammo["GREEN_GRENADE"] = weapon_config.green_grenade.ammount_of_bullets;
    gun_ammo["HOLY_GRENADE"] = weapon_config.holy_grenade.ammount_of_bullets;
    gun_ammo["DYNAMITE"] = weapon_config.dynamite.ammount_of_bullets;
    gun_ammo["RED_GRENADE"] = weapon_config.red_grenade.ammount_of_bullets;
    gun_ammo["AIR_STRIKE"] = weapon_config.air_strike.ammount_of_bullets;

}

void SdlWorm::render_same() {
    if (health <= 0)
        return;
    texture_manager.render(worm_state, animation_phase, x_pos - camera.get_x(), y_pos - camera.get_y(), flip);
    health_bar.set_position(x_pos - camera.get_x(), y_pos - 10 - camera.get_y());
    health_bar.set_width(health/2);
    health_bar.set_delim_position(x_pos -1 - camera.get_x(), y_pos -11 - camera.get_y());
    health_bar.set_delim_width((health/2) + 2);
    
    if (attack_power > 0) {
        attack_power_bar.set_position(x_pos - camera.get_x(), y_pos - camera.get_y() + 50);
        attack_power_bar.set_width(attack_power/2);
        attack_power_bar.render(renderer);
    }
    
    health_bar.render(renderer);
    worm_state->render_ammo(renderer, gun_ammo[worm_state->get_name()], 0,0);
}

int SdlWorm::projectile_id() {
    return worm_state->projectile_id();
}

void SdlWorm::render_new(Vect2D position, int state) {
    //aca obtendria el state, y haria un super switch case y le actualizaria el worm_state
    // cuando muere un worm, me pasan su estado de muerte y despues veo que onda
    if (worm_state == worm_states["DIE"])
        return;
    /*if (state == SE_MURIO) {
        worm_state = worm_states["DIE"];
        play_animation();
    }*/
    

    x_pos = position.x;
    y_pos = position.y;
    std::cout << x_pos << " : " << y_pos << std::endl;
    if (is_animation_playing) {
        texture_manager.render(worm_state, animation_phase, position.x - camera.get_x(), position.y - camera.get_y(), flip);
    } else {
        texture_manager.render(worm_state, animation_phase, position.x - camera.get_x(), position.y - camera.get_y(), flip);
    }

    health_bar.set_position(x_pos - camera.get_x(), y_pos - 10 - camera.get_y());
    health_bar.set_width(health/2);
    health_bar.set_delim_position(x_pos -1 - camera.get_x(), y_pos -11 - camera.get_y());
    health_bar.set_delim_width((health/2) + 2);

    if (attack_power > 0) {
        attack_power_bar.set_position(x_pos - camera.get_x(), y_pos - camera.get_y() + 50);
        attack_power_bar.set_width(attack_power/2);
        attack_power_bar.render(renderer);
    }
    
    

    health_bar.render(renderer);
    worm_state->render_ammo(renderer, gun_ammo[worm_state->get_name()], camera.get_x(), camera.get_y());
}

void SdlWorm::apply() {
    if (is_charging) { 
        attack_power = attack_power + 1;
        if (attack_power >= 100) {
            attack_power = 100;
        }
    }
}

void SdlWorm::set_color() {
    attack_power_bar.set_color(255, 0, 0);
    health_bar.set_delim_color(204, 102, 0);
    switch (player_id)
    {
    case 0:
        health_bar.set_color(0, 0, 255);
        break;
    case 1:
        health_bar.set_color(0, 255, 0);
        break;
    case 2:
        health_bar.set_color(255, 0, 0);
        break;
    case 3:
        health_bar.set_color(0, 255, 255);
        break;
    case 4:
        health_bar.set_color(255, 0, 255);
        break;
    case 5:
        health_bar.set_color(255, 255, 0);
        break;
    case 6:
        health_bar.set_color(128, 192, 192);
        break;
    case 7:
        health_bar.set_color(192, 192, 128);
        break;
    case 8:
        health_bar.set_color(192, 128, 192);
        break;
        
    default:
        health_bar.set_color(192, 128, 128);
        break;
    }

}

SdlWorm::SdlWorm(SdlCamera& camera, Renderer& renderer, SdlWormTextureManager& texture_manager, SdlSoundManager& sound_manager, int x_pos, int y_pos, int worm_id, int player_id, int health) :
x_pos(x_pos), y_pos(y_pos),
camera(camera), renderer(renderer), texture_manager(texture_manager), sound_manager(sound_manager),
health(health),  health_bar(x_pos, y_pos, 10, (health/2))

 {
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
    health_bar.set_height(10);
    health_bar.set_delim_height(12);
    health_bar.set_width(health/2);
    health_bar.set_delim_width((health/2) + 2);
    attack_power_bar.set_height(10);
    attack_power_bar.set_delim_height(0);
    attack_power_bar.set_width(attack_power);
    attack_power_bar.set_delim_width(0);


    set_color();
    CommonConfigurationParser configuration_parser;
    worm_config = configuration_parser.get_worm_configuration();
    weapon_config = configuration_parser.get_weapons_configuration();




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
    worm_states["DIE"] = new SdlWormStateDie();

    

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
