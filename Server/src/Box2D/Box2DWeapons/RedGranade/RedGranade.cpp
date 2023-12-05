#include "RedGranade.h"
#include "../../Box2dManager/box2dManager.h"

RedGranade::RedGranade(BoxManager* box_manager): box_manager(box_manager) {}

void RedGranade::fire(float angle, float strength, float restitution, bool has_to_wait, bool wind) {
    int type = RED_GRANADE;
    box_manager->fire_projectile(angle, strength, restitution, RED_GRANADE, WORM | BEAM, has_to_wait, type, wind);
}

RedGranade::~RedGranade() {}
