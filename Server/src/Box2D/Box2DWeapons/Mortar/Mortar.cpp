#include "Mortar.h"
#include "../../Box2dManager/box2dManager.h"

Mortar::Mortar(BoxManager* box_manager): box_manager(box_manager) {}

void Mortar::fire(float angle, float strength, float restitution, bool has_to_wait, bool wind) {
    int type = MORTAR;
    box_manager->fire_projectile(angle, strength, restitution, MORTAR, WORM | BEAM, has_to_wait, type, wind);
}

Mortar::~Mortar() {}
