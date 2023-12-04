#include "BaseballBat.h"
#include "../../Box2dManager/box2dManager.h"

BaseballBat::BaseballBat(BoxManager* box_manager): box_manager(box_manager) {}

void BaseballBat::fire(float angle, float strength) {
    box_manager->baseball_bat(angle, strength);
}

BaseballBat::~BaseballBat() {}
