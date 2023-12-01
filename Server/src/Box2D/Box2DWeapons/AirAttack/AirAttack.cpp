#include "AirAttack.h"

AirAttack::AirAttack(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void AirAttack::fire(float angle, float strength) {
    box_manager->fire_projectile(angle, strength, 0.1f, AIR_STRIKE, WORM | BEAM);
}

AirAttack::~AirAttack() {}
