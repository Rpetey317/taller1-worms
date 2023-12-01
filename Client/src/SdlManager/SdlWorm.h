#pragma once
#include <map>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLImage.hh>
#include "SdlSoundManager.h"
#include "SdlWormTextureManager.h"
#include "SdlWormState.h"
#include "SdlWormStateAirStrike.h"
#include "SdlWormStateBanana.h"
#include "SdlWormStateBazooka.h"
#include "SdlWormStateBeisboll.h"
#include "SdlWormStateDynamite.h"
#include "SdlWormStateFalling.h"
#include "SdlWormStateGreenGrenade.h"
#include "SdlWormStateHolyGrenade.h"
#include "SdlWormStateMortar.h"
#include "SdlWormStateRedGrenade.h"
#include "SdlWormStateStill.h"
#include "SdlWormStateTeleport.h"
#include "SdlWormStateWalk.h"

using namespace SDL2pp;  // NOLINT

class SdlWorm {
public:
    int x_pos;
    int y_pos;
    SDL_RendererFlip flip;
    bool is_charging;
    int attack_power;
    int worm_id;
    explicit SdlWorm(Renderer& renderer, SdlWormTextureManager& texture_manager, SdlSoundManager& sound_manager, int x_pos, int y_pos, int worm_id, int player_id, int health);
    bool next_animation();
    void change_state(std::string state);
    void play_sound(std::string sound_to_play);
    void render_new(Vect2D position);
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
    bool is_animation_playing;
private:
    void set_color();
    Renderer &renderer;
    SdlWormTextureManager& texture_manager;
    SdlSoundManager& sound_manager;
    int player_id;
    int angle;
    int animation_phase;
    int health;
    int initial_health;
    Color color;
    Color delim_color;
    Rect health_bar;
    Rect health_bar_delim;
    SdlWormState *worm_state;
    std::map<std::string, SdlWormState*> worm_states;
    std::map<std::string, int> gun_ammo;

};
