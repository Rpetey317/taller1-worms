#ifndef WEAPON_DTO_H
#define WEAPON_DTO_H

#include "Vect2D.h"

class WeaponDTO {
public:
    int id;
    Vect2D position;
    int angle;

    WeaponDTO();
    WeaponDTO(int id, Vect2D position, int angle);

    int get_id();
    Vect2D get_position();
    int get_angle();

};

#endif // WEAPON_DTO_H
