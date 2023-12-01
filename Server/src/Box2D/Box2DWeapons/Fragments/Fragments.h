#ifndef _FRAGMENTS_H_
#define _FRAGMENTS_H_

#include "../Weapons.h"

class Fragments : public B2dWeapon {
    BoxManager* box_manager;
public:
    explicit Fragments(BoxManager* box_manager);

    void fire(float angle, float strength) override;

    ~Fragments();

};

#endif // _FRAGMENTS_H_
