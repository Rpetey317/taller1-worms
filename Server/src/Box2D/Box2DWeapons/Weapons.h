#ifndef _Weapons_H_
#define _Weapons_H_

#include "../../../../libs/box2d/include/box2d/box2d.h"
#include "../Box2dManager/box2dManager.h"


class B2dWeapon {
public:
    B2dWeapon() = default;

    virtual void fire(float angle, float strength, float restitution, bool timer, bool wind) = 0;

    virtual ~B2dWeapon() = default;
};

class B2dWeaponSpecial{
public:
    B2dWeaponSpecial() = default;

    virtual void fire_special(Vect2D position) = 0;

    virtual ~B2dWeaponSpecial() = default;
};


#endif  // !_Weapons_H_
