#include "SdlProjectile.h"


void SdlProjectile::render() {
        projectile_texture_manager.render("NOMBRE", x_pos, y_pos, angle);
}

