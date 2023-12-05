#include "HolyGranade.h"
#include "../../Box2dManager/box2dManager.h"

HolyGranade::HolyGranade(BoxManager* box_manager): box_manager(box_manager) {}

void HolyGranade::fire(float angle, float strength, float restitution, bool has_to_wait, bool wind) {
    int type = HOLY_GRANADE;
    box_manager->fire_projectile(angle, strength, restitution, HOLY_GRANADE, WORM | BEAM, has_to_wait, type, wind);
}

HolyGranade::~HolyGranade() {}
