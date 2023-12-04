#ifndef _AIR_ATTACK_H
#define _AIR_ATTACK_H

#include "../Weapons.h"

class AirAttack : public B2dWeaponSpecial {
    class BoxManager* box_manager;
public:
    explicit AirAttack(BoxManager* box_manager);

    void fire_special(Vect2D position) override;
    ~AirAttack();

};

#endif // _AIR_ATTACK_H
