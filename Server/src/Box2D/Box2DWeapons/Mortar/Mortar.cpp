#include "Mortar.h"
#include "../../Box2dManager/box2dManager.h"

Mortar::Mortar(BoxManager* box_manager): box_manager(box_manager) {}

void Mortar::fire(float angle, float strength) {
    int type = MORTAR;
    box_manager->fire_projectile(angle, strength, 0.0, MORTAR, WORM | BEAM, true, type);
}

Mortar::~Mortar() {}
