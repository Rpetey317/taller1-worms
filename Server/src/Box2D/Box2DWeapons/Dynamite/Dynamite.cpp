#include "Dynamite.h"
#include "../../Box2dManager/box2dManager.h"

Dynamite::Dynamite(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void Dynamite::fire(float angle, float strength) {
    box_manager->dynamite(0.0f, DYNAMITE, WORM | BEAM);
}

Dynamite::~Dynamite() {}
