#include "Bazooka.h"
#include "../../Box2dManager/box2dManager.h"

Bazooka::Bazooka(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void Bazooka::fire(float angle, float strength) {
    int type = BAZOOKA;
    box_manager->fire_projectile(angle, strength, 0.0, BAZOOKA, WORM | BEAM, true, type);
}

Bazooka::~Bazooka() {}
