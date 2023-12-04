#include "GreenGranade.h"
#include "../../Box2dManager/box2dManager.h"

GreenGranade::GreenGranade(BoxManager* box_manager) {
    this->box_manager = box_manager;
}

void GreenGranade::fire(float angle, float strength) {
    int type = GREEN_GRANADE;
    box_manager->fire_projectile(angle, strength, 0.25, GREEN_GRANADE, WORM | BEAM, false, type);
}

GreenGranade::~GreenGranade() {}
