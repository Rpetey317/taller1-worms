#ifndef _AIR_ATTACK_H
#define _AIR_ATTACK_H

#include "../Weapons.h"

class AirAttack : public B2dWeapon {
    BoxManager* box_manager;
public:
    explicit AirAttack(BoxManager* box_manager);

    void fire(float angle, float strength) override;

    ~AirAttack();

};

#endif // _AIR_ATTACK_H
