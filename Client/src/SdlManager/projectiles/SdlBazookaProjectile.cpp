#include "SdlBazookaProjectile.h"


SdlBazookaProjectile::SdlBazookaProjectile(
        SdlSoundManager& sound_manager, SdlProjectilesTextureManager& projectile_texture_manager, SdlCamera& camera) : SdlProjectile(sound_manager, projectile_texture_manager, camera) {}

void SdlBazookaProjectile::render(int x_pos, int y_pos, int angle) {
    std::string name("BAZOOKA");
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->angle = angle;
    projectile_texture_manager.render(name, x_pos - camera.get_x(), y_pos - camera.get_y(), angle, 0);
}

void SdlBazookaProjectile::play_sound() {
    sound_manager.play_sound("MISSILE_EXPLODING_SOUND");
}
