#ifndef _BASEBALL_BAT_H_
#define _BASEBALL_BAT_H_

#include "../Weapons.h"

class BaseballBat : public B2dWeapon {
    BoxManager* box_manager;
public:
    explicit BaseballBat(BoxManager* box_manager);

    void fire(float angle, float strength) override;

    ~BaseballBat();

};

#endif
