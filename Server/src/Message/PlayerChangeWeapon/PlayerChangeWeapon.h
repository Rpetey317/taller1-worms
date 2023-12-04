#ifndef __PLAYERCHANGEWEAPON_H__
#define __PLAYERCHANGEWEAPON_H__

#include <memory>

#include "../Message.h"

class PlayerChangeWeapon: public Message {
    int type_weapon;
public:
    explicit PlayerChangeWeapon(const int& _id);

    std::shared_ptr<Update> get_processed_by(Game& game) override;

    ~PlayerChangeWeapon() override = default;
};

#endif  // !__PLAYERCHANGEWEAPOM_H__
