#include "SdlHolyGrenadeProjectile.h"


SdlHolyGrenadeProjectile::SdlHolyGrenadeProjectile(
        SdlSoundManager& sound_manager, SdlProjectilesTextureManager& projectile_texture_manager, SdlCamera& camera) : SdlProjectile(sound_manager, projectile_texture_manager, camera) {}

void SdlHolyGrenadeProjectile::render(int x_pos, int y_pos, int angle) {
std::string name("HOLY_GRENADE");
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->angle = angle;
    projectile_texture_manager.render(name, x_pos, y_pos, angle, 0);
}

void SdlHolyGrenadeProjectile::play_sound() {
    sound_manager.play_sound("HOLY_GRENADE_EXPLODING_SOUND");
}

