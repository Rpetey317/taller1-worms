#pragma once
#include <map>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLImage.hh>
#include "../states/common_states.h"
#include "../texture_sound_manager/SdlSoundManager.h"
#include "../texture_sound_manager/SdlWormTextureManager.h"
#include "../../../Common/Vect2D.h"
#include "../../../Common/CommonConfigurationParser.h"
#include "SdlResizableRect.h"

using namespace SDL2pp;  // NOLINT

class SdlWorm {
public:
    int x_pos;
    int y_pos;
    SDL_RendererFlip flip;
    bool is_charging = false;
    int attack_power;
    int worm_id;
    int player_id;
    explicit SdlWorm(SdlCamera& camera, Renderer& renderer, SdlWormTextureManager& texture_manager, SdlSoundManager& sound_manager, int x_pos, int y_pos, int worm_id, int player_id, int health);
    bool next_animation();
    void change_state(std::string state);
    void play_sound();
    void render_new(Vect2D position, int state);
    void render_same();
    void destroy();
    void apply();
    bool is_in_gun_state();
    void change_angle(int angle);
    bool reduce_ammo();
    bool has_ammo();
    void play_animation();
    void recharge_ammo();
    void set_health(int ammount_to_heal);
    int projectile_id();
    bool is_animation_playing;
    int angle;
    bool already_fired = false;
private:
    SdlCamera &camera;
    Renderer &renderer;
    SdlWormTextureManager& texture_manager;
    SdlSoundManager& sound_manager;
    int animation_phase;
    int health;
    int initial_health;
    SdlResizableRect health_bar;
    SdlResizableRect attack_power_bar;

    SdlWormState *worm_state;
    std::map<std::string, SdlWormState*> worm_states;
    std::map<std::string, int> gun_ammo;
    WormConfiguration worm_config;
    WeaponsConfiguration weapon_config;
    void set_color();

};
