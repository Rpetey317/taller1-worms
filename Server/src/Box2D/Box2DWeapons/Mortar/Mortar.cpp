#include "Mortar.h"

Mortar::Mortar(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void Mortar::fire(float angle, float strength) {
    box_manager->fire_projectile(angle, strength, 0.0, MORTAR, WORM | BEAM);
}

Mortar::~Mortar() {}
