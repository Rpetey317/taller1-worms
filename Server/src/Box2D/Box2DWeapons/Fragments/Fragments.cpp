#include "Fragments.h"

Fragments::Fragments(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void Fragments::fire(float angle, float strength) {
    box_manager->fire_projectile(angle, strength, 0.0, FRAGMENT, WORM | BEAM);
}

Fragments::~Fragments() {}