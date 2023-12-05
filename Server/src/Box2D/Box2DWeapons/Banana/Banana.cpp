#include "Banana.h"
#include "../../Box2dManager/box2dManager.h"

Banana::Banana(BoxManager* box_manager): box_manager(box_manager) {}

void Banana::fire(float angle, float strength, float restitution, bool has_to_wait, bool wind) {
    int type = BANANA;
    box_manager->fire_projectile(angle, strength, restitution, BANANA, WORM | BEAM, has_to_wait, type, wind);
}

Banana::~Banana() {}
