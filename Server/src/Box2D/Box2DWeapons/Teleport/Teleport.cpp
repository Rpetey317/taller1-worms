#include "Teleport.h"

Teleport::Teleport(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void Teleport::fire(float angle, float strength) {
    box_manager->fire_projectile(angle, strength, 0.0, TELEPORT, WORM | BEAM);
}

Teleport::~Teleport() {}
