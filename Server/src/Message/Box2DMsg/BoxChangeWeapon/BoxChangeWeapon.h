#ifndef __BOXCHANGEWEAPON_H__
#define __BOXCHANGEWEAPON_H__

#include "../Box2DMsg.h"

class BoxChangeWeapon: public Box2DMsg {
    int weapon_id;

public:
    BoxChangeWeapon(int plid, int weapon_id);

    int get_cmd() override;

    int get_weapon_id() const;

    ~BoxChangeWeapon();
};

#endif // !__BOXCHANGEWEAPON_H__
