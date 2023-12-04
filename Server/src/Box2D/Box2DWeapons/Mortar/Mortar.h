#ifndef _MORTAR_H_
#define _MORTAR_H_

#include "../Weapons.h"

class Mortar : public B2dWeapon {
    class BoxManager* box_manager;
public:
    explicit Mortar(BoxManager* box_manager);

    void fire(float angle, float strength) override;

    ~Mortar();

};

#endif // _MORTAR_H_
