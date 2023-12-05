#include "Bazooka.h"
#include "../../Box2dManager/box2dManager.h"

Bazooka::Bazooka(BoxManager* box_manager): box_manager(box_manager) {}

void Bazooka::fire(float angle, float strength, float restitution, bool has_to_wait, bool wind) {
    int type = BAZOOKA;
    box_manager->fire_projectile(angle, strength, restitution, BAZOOKA, WORM | BEAM, has_to_wait, type, wind);
}

Bazooka::~Bazooka() {}
