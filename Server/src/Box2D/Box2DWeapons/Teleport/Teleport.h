#ifndef _TELEPORT_H_
#define _TELEPORT_H_

#include "../Weapons.h"

class Teleport : public B2dWeaponSpecial {
    class BoxManager* box_manager;
public:
    explicit Teleport(BoxManager* box_manager);

    void fire_special(Vect2D position) override;

    ~Teleport();

};

#endif // _TELEPORT_H_
