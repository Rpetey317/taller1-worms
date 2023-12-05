#ifndef _BASEBALL_BAT_H_
#define _BASEBALL_BAT_H_

#include "../Weapons.h"

class BaseballBat : public B2dWeapon {
    BoxManager* box_manager;
public:
    explicit BaseballBat(BoxManager* box_manager);

    void fire(float angle, float strength, float restitution, bool has_to_wait, bool wind) override;
    
    ~BaseballBat();

};

#endif // _BASEBALL_BAT_H_
