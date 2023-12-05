#ifndef _RED_GRANADE_H_
#define _RED_GRANADE_H_

#include "../Weapons.h"

class RedGranade : public B2dWeapon {
    class BoxManager* box_manager;
public:
    explicit RedGranade(BoxManager* box_manager);

    void fire(float angle, float strength, float restitution, bool has_to_wait, bool wind) override;

    ~RedGranade();

};

#endif // _RED_GRANADE_H_
