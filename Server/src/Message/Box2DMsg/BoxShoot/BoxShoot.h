#ifndef __BOXSHOOT_H__
#define __BOXSHOOT_H__

#include "../Box2DMsg.h"

class BoxShoot : public Box2DMsg {
    int weapon_id;
    int power;
    int angle;

public:
    BoxShoot(int plid, int weapon_id, int power, int angle);

    // void get_processed_box2d(BoxManager& box2d) override;

    int get_weapon_id() const;
    int get_power() const;
    int get_angle() const;
};

#endif // !__BOXSHOOT_H__
