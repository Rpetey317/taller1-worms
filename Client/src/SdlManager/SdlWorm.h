#pragma once

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLImage.hh>
#include "SdlSoundManager.h"
#include "SdlWormTextureManager.h"
#include "SdlWormState.h"
#include "SdlWormStateStill.h"
using namespace SDL2pp;  // NOLINT

class SdlWorm {
public:
    int x_pos;
    int y_pos;
    int animation_phase;
    int angle;
    SDL_RendererFlip flip;
    SdlWormState *worm_state;
    int attack_power;
    bool is_charging;
    explicit SdlWorm(SdlWormTextureManager& texture_manager, SdlSoundManager& sound_manager);
    void next_animation();
    void play_sound(std::string sound_to_play);
    void render_new(Rect rect);
    void render_same();
    void destroy();
    void apply();

private:
    SdlWormTextureManager& texture_manager;
    SdlSoundManager& sound_manager;

};
