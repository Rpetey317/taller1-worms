#include "Banana.h"
#include "../../Box2dManager/box2dManager.h"

Banana::Banana(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void Banana::fire(float angle, float strength) {
    box_manager->fire_projectile(angle, strength, 0.5, BANANA, WORM | BEAM);
}

Banana::~Banana() {}
