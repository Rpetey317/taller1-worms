#pragma once

#include "SdlProjectile.h"


class SdlRedGrenadeProjectile : public SdlProjectile {
public:
    SdlRedGrenadeProjectile(SdlSoundManager& sound_manager, SdlProjectilesTextureManager& projectile_texture_manager, SdlCamera& camera);
    void render(int x_pos, int y_pos, int angle) override;

};

