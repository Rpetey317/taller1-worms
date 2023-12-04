#include "Banana.h"
#include "../../Box2dManager/box2dManager.h"

Banana::Banana(BoxManager* box_manager): box_manager(box_manager) {}

void Banana::fire(float angle, float strength) {
    int type = BANANA;
    box_manager->fire_projectile(angle, strength, 0.5, BANANA, WORM | BEAM, false, type);
}

Banana::~Banana() {}
