#ifndef _DYNAMITE_H_
#define _DYNAMITE_H_

#include "../Weapons.h"

class Dynamite : public B2dWeapon {
    BoxManager* box_manager;
public:
    explicit Dynamite(BoxManager* box_manager);

    void fire(float angle, float strength, float restitution, bool has_to_wait, bool wind) override;

    ~Dynamite();

};

#endif // _DYNAMITE_H_
