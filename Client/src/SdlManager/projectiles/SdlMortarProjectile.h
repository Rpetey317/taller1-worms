#pragma once

#include "SdlProjectile.h"


class SdlMortarProjectile : public SdlProjectile {
public:
    SdlMortarProjectile(SdlSoundManager& sound_manager, SdlProjectilesTextureManager& projectile_texture_manager, SdlCamera& camera);
    void render(int x_pos, int y_pos, int angle) override;

};

