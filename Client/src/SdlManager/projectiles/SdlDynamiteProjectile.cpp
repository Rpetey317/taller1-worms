#include "SdlDynamiteProjectile.h"


SdlDynamiteProjectile::SdlDynamiteProjectile(
        SdlProjectilesTextureManager& projectile_texture_manager, SdlCamera& camera) : SdlProjectile(projectile_texture_manager, camera) {}

void SdlDynamiteProjectile::render(int x_pos, int y_pos, int angle) {
std::string name("DYNAMITE");
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->angle = angle;
    projectile_texture_manager.render(name, x_pos, y_pos, angle, 0);
}