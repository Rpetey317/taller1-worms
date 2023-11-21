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
    explicit SdlWorm(SdlWormTextureManager& texture_manager, SdlSoundManager& sound_manager);
    void next_animation();
    void change_state(std::string state);
    void play_sound(std::string sound_to_play);
    void render_new(Rect rect);
    void render_same();
    void destroy();
    void apply();
    bool is_in_gun_state();
    void change_angle(int angle);

private:
    int angle;
    SdlWormTextureManager& texture_manager;
    SdlSoundManager& sound_manager;
    int animation_phase;
    
    SdlWormState *worm_state;
    std::map<std::string, SdlWormState*> worm_states;

};
