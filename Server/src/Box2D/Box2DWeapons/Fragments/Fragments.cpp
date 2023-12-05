#include "Fragments.h"
#include "../../Box2dManager/box2dManager.h"

Fragments::Fragments(BoxManager* box_manager): box_manager(box_manager) {}

void Fragments::fire(float angle, float strength, float restitution, bool has_to_wait, bool wind) {
    int type = FRAGMENT;
    box_manager->fire_projectile(angle, strength, restitution, FRAGMENT, WORM | BEAM, has_to_wait, type, wind);
}

Fragments::~Fragments() {}