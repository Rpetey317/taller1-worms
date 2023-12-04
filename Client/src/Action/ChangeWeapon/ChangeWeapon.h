#ifndef CHANGEWEAPON_H_
#define CHANGEWEAPON_H_

#include <string>
#include <vector>

#include "../Action.h"

class ChangeWeapon: public Action {
private:
    int type_weapon;

public:
    explicit ChangeWeapon(int type_weapon);

    char get_send_by(ClientProtocol& prot) override;

    int get_type_weapon();
};

#endif  // CHANGEWEAPON_H_
