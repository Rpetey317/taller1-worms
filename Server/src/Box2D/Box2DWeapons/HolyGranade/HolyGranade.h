#ifndef _HOLY_GRANADE_H
#define _HOLY_GRANADE_H

#include "../Weapons.h"

class HolyGranade : public B2dWeapon {
    BoxManager* box_manager;
public:
    explicit HolyGranade(BoxManager* box_manager);

    void fire(float angle, float strength) override;

    ~HolyGranade();

};

#endif // _HOLY_GRANADE_H
