#include "SdlBananaProjectile.h"


SdlBananaProjectile::SdlBananaProjectile(SdlSoundManager& sound_manager, SdlProjectilesTextureManager& projectile_texture_manager, SdlCamera& camera) : SdlProjectile(sound_manager, projectile_texture_manager, camera) {
}

void SdlBananaProjectile::render(int x_pos, int y_pos, int angle) {
std::string name("BANANA");
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->angle = angle;
    projectile_texture_manager.render(name, x_pos - camera.get_x(), y_pos - camera.get_y(), angle, 0);
}

void SdlBananaProjectile::play_sound() {
    sound_manager.play_sound("BANANA_EXPLODING_SOUND");
}
