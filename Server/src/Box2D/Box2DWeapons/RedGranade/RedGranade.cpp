#include "RedGranade.h"
#include "../../Box2dManager/box2dManager.h"

RedGranade::RedGranade(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void RedGranade::fire(float angle, float strength) {
    int type = RED_GRANADE;
    box_manager->fire_projectile(angle, strength, 0.25, RED_GRANADE, WORM | BEAM, false, type);
}

RedGranade::~RedGranade() {}
