#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "../SdlCamera.h"
#include "../texture_sound_manager/SdlSoundManager.h"
#include "../texture_sound_manager/SdlProjectilesTextureManager.h"


using namespace SDL2pp;  // NOLINT

class SdlProjectile {
public:
    SdlProjectile(SdlSoundManager& sound_manager, SdlProjectilesTextureManager& projectile_texture_manager, SdlCamera& camera);
    virtual ~SdlProjectile();
    virtual void render(int x_pos, int y_pos, int angle) {return;};
    virtual int get_pos_x() {return x_pos;};
    virtual int get_pos_y() {return y_pos;};
    virtual void play_animation(bool *is_animation_playing);   
    virtual void play_sound() {sound_manager.play_sound("MISSILE_EXPLODING_SOUND");};


protected:
    int x_pos;
    int y_pos;
    int angle;
    bool is_animation_playing = false;
    int animation_phase = 0;
    SdlSoundManager& sound_manager;
    SdlProjectilesTextureManager& projectile_texture_manager;
    SdlCamera &camera;

};
