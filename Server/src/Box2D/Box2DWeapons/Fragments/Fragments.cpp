#include "Fragments.h"
#include "../../Box2dManager/box2dManager.h"

Fragments::Fragments(BoxManager* box_manager): box_manager(box_manager) {}

void Fragments::fire(float angle, float strength) {
    int type = FRAGMENT;
    box_manager->fire_projectile(angle, strength, 0.0, FRAGMENT, WORM | BEAM, true, type);
}

Fragments::~Fragments() {}