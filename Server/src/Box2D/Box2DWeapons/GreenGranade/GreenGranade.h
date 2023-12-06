#ifndef _GREEN_GRANADE_H_
#define _GREEN_GRANADE_H_

#include "../Weapons.h"

class GreenGranade : public B2dWeapon {
    class BoxManager* box_manager;
public:
    explicit GreenGranade(BoxManager* box_manager);

    void fire(float angle, float strength) override;

    ~GreenGranade();

};

#endif
