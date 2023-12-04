#ifndef _Weapons_H_
#define _Weapons_H_

#include "../../../../libs/box2d/include/box2d/box2d.h"
#include "../Box2dManager/box2dManager.h"

enum _entityCategory {
    BEAM = 0x0001,
    WORM = 0x0002,
    BAZOOKA = 0x0003,
    MORTAR = 0x0004,
    GREEN_GRANADE = 0x0005,
    RED_GRANADE = 0x0006,
    BANANA = 0x0007,
    HOLY_GRANADE = 0x0008,
    AIR_STRIKE = 0x0009,
    FRAGMENT = 0x0010,
    AIR_MISSLE = 0x0011,
    TELEPORT = 0x0012,
    DYNAMITE = 0x0013,
    BASEBALL_BAT = 0x0014,
  };

class B2dWeapon {
public:
    B2dWeapon() = default;

    virtual void fire(float angle, float strength) = 0;

    virtual ~B2dWeapon() = default;
};

class B2dWeaponSpecial{
public:
    B2dWeaponSpecial() = default;

    virtual void fire_special(Vect2D position) = 0;

    virtual ~B2dWeaponSpecial() = default;
};


#endif  // !_Weapons_H_
