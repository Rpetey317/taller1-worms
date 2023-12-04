#include "WeaponDTO.h"

WeaponDTO::WeaponDTO() {}

WeaponDTO::WeaponDTO(int id, Vect2D position, int angle):
        id(id), position(position), angle(angle) {}

int WeaponDTO::get_id() { return this->id; }

Vect2D WeaponDTO::get_position() { return this->position; }

int WeaponDTO::get_angle() { return this->angle; }
