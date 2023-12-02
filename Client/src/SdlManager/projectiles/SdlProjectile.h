#pragma once
#include <SDL2pp/SDL2pp.hh>

#include "../texture_sound_manager/SdlProjectilesTextureManager.h"


using namespace SDL2pp;  // NOLINT

class SdlProjectile {
public:
    SdlProjectile();
    virtual void render(Renderer& renderer, int x_pos, int y_pos, int angle) = 0;
    virtual int get_pos_x() {return x_pos;};
    virtual int get_pos_y() {return y_pos;};
    virtual void play_animation() {/*codigo muy lindo para hacer una explosion :)*/};


private:
    int x_pos;
    int y_pos;
    SdlCamera &camera;
    //SdlProjectilesTextureManager& projectile_texture_manager;
    SdlProjectilesTextureManager& projectile_texture_manager;

};
