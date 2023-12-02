#include "Bazooka.h"
#include "../../Box2dManager/box2dManager.h"

Bazooka::Bazooka(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void Bazooka::fire(float angle, float strength) {
    box_manager->fire_projectile(angle, strength, 0.0, BAZOOKA, WORM | BEAM);
}

Bazooka::~Bazooka() {}
