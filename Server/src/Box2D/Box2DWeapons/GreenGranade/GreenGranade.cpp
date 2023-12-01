#include "GreenGranade.h"

GreenGranade::GreenGranade(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void GreenGranade::fire(float angle, float strength) {
    box_manager->fire_projectile(angle, strength, 0.25, GREEN_GRANADE, WORM | BEAM);
}

GreenGranade::~GreenGranade() {}
