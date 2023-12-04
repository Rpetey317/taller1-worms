#include "Teleport.h"
#include "../../Box2dManager/box2dManager.h"

Teleport::Teleport(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void Teleport::fire_special(Vect2D position) {
    box_manager->teleport(position);
}

Teleport::~Teleport() {}
