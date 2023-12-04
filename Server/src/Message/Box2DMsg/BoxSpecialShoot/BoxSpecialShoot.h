#ifndef __BOXSPSHOOT_H__
#define __BOXSPSHOOT_H__

#include "../Box2DMsg.h"

#include "Vect2D.h"

class BoxSpecialShoot: public Box2DMsg {
    int weapon_id;
    Vect2D position;

public:
    BoxSpecialShoot(int plid, int weapon_id, Vect2D position);

    int get_cmd() override;

    int get_weapon_id() const;
    Vect2D get_position() const;
};

#endif  // !__BOXSPSHOOT_H__
