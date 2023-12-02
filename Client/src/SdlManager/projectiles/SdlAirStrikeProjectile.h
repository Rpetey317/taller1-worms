#pragma once
#include "SdlProjectile.h"


class SdlAirStrikeProjectile : public SdlProjectile {
public:
    SdlAirStrikeProjectile(SdlProjectilesTextureManager& projectile_texture_manager, SdlCamera& camera);
    void render(int x_pos, int y_pos, int angle) override;

};

