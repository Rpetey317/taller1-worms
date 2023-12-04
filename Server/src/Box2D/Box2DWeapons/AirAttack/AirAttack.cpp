#include "AirAttack.h"
#include "../../Box2dManager/box2dManager.h"

AirAttack::AirAttack(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void AirAttack::fire_special(Vect2D position) {
    box_manager->air_strike(position);
}

AirAttack::~AirAttack() {}
