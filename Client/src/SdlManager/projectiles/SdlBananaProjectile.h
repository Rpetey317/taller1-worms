
#pragma once

#include "SdlProjectile.h"


class SdlBananaProjectile : public SdlProjectile {
public:
    SdlBananaProjectile(SdlSoundManager& sound_manager, SdlProjectilesTextureManager& projectile_texture_manager, SdlCamera& camera);
    void render(int x_pos, int y_pos, int angle) override;
    void play_sound() override;
};

