#include "HolyGranade.h"

HolyGranade::HolyGranade(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void HolyGranade::fire(float angle, float strength) {
    box_manager->fire_projectile(angle, strength, 0.25, HOLY_GRANADE, WORM | BEAM);
}

HolyGranade::~HolyGranade() {}
