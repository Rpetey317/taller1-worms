#include "BoxShoot.h"

#include "Box2dManager/box2dManager.h"

BoxShoot::BoxShoot(int plid, int weapon_id, int power, int angle):
        Box2DMsg(plid, 0), weapon_id(weapon_id), power(power), angle(angle) {}

int BoxShoot::get_cmd() { return COMMAND_SHOOT; }

int BoxShoot::get_weapon_id() const { return this->weapon_id; }

int BoxShoot::get_power() const { return this->power; }

int BoxShoot::get_angle() const { return this->angle; }
