#include "GreenGranade.h"
#include "../../Box2dManager/box2dManager.h"

GreenGranade::GreenGranade(BoxManager* box_manager): box_manager(box_manager) {}

void GreenGranade::fire(float angle, float strength, float restitution, bool has_to_wait, bool wind) {
    int type = GREEN_GRANADE;
    box_manager->fire_projectile(angle, strength, restitution, GREEN_GRANADE, WORM | BEAM, has_to_wait, type, wind);
}

GreenGranade::~GreenGranade() {}
