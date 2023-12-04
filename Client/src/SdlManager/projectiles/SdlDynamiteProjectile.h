#pragma once

#include "SdlProjectile.h"


class SdlDynamiteProjectile : public SdlProjectile {
public:
    SdlDynamiteProjectile(SdlProjectilesTextureManager& projectile_texture_manager, SdlCamera& camera);
    void render(int x_pos, int y_pos, int angle) override;

};

