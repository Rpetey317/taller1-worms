#pragma once

#include "SdlProjectile.h"


class SdlGreenGrenadeProjectile : public SdlProjectile {
public:
    SdlGreenGrenadeProjectile(SdlProjectilesTextureManager& projectile_texture_manager, SdlCamera& camera);
    void render(int x_pos, int y_pos, int angle) override;

};

