#include "SdlProjectile.h"


SdlProjectile::SdlProjectile(SdlSoundManager& sound_manager ,SdlProjectilesTextureManager& projectile_texture_manager, SdlCamera& camera) : sound_manager(sound_manager), projectile_texture_manager(projectile_texture_manager), camera(camera) {
        x_pos = y_pos = angle = 0;
}

SdlProjectile::~SdlProjectile() {}

void SdlProjectile::play_animation(bool *is_animation_playing) {
        projectile_texture_manager.render_explosion(x_pos - camera.get_x(), y_pos - camera.get_y(), animation_phase);
        animation_phase++;
        if (animation_phase >= 20) {
                animation_phase = 0;
                (*is_animation_playing) = false;
        }

}
