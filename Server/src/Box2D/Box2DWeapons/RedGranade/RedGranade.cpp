#include "RedGranade.h"

RedGranade::RedGranade(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void RedGranade::fire(float angle, float strength) {
    box_manager->fire_projectile(angle, strength, 0.25, RED_GRANADE, WORM | BEAM);
}

RedGranade::~RedGranade() {}
