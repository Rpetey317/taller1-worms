#ifndef _BANANA_H
#define _BANANA_H

#include "../Weapons.h"

class Banana : public B2dWeapon {
    class BoxManager* box_manager;
public:
    explicit Banana(BoxManager* box_manager);

    void fire(float angle, float strength) override;

    ~Banana();

};

#endif // _BANANA_H
