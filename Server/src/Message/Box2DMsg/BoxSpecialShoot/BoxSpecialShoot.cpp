#include "BoxSpecialShoot.h"


BoxSpecialShoot::BoxSpecialShoot(int plid, int weapon_id, Vect2D position):
        Box2DMsg(plid, 0), weapon_id(weapon_id), position(position) {}

int BoxSpecialShoot::get_cmd() { return COMMAND_SPECIAL_SHOOT; }

int BoxSpecialShoot::get_weapon_id() const { return this->weapon_id; }

Vect2D BoxSpecialShoot::get_position() const { return this->position; }
