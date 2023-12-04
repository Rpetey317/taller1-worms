#include "HolyGranade.h"
#include "../../Box2dManager/box2dManager.h"

HolyGranade::HolyGranade(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void HolyGranade::fire(float angle, float strength) {
    int type = HOLY_GRANADE;
    box_manager->fire_projectile(angle, strength, 0.25, HOLY_GRANADE, WORM | BEAM, false, type);
}

HolyGranade::~HolyGranade() {}
