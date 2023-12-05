#include "Dynamite.h"
#include "../../Box2dManager/box2dManager.h"

Dynamite::Dynamite(BoxManager* box_manager): box_manager(box_manager) {}

void Dynamite::fire(float angle, float strength, float restitution, bool has_to_wait, bool wind) {
    box_manager->dynamite(restitution, DYNAMITE, WORM | BEAM, has_to_wait);
}

Dynamite::~Dynamite() {}
