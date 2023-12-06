#ifndef _BAZOOKA_H_
#define _BAZOOKA_H_

#include "../Weapons.h"

class Bazooka : public B2dWeapon {
    class BoxManager* box_manager;
public:
    explicit Bazooka(BoxManager* box_manager);

    void fire(float angle, float strength) override;

    ~Bazooka();

};

#endif
