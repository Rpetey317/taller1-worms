#ifndef SHOOT_H_
#define SHOOT_H_

#include <string>
#include <vector>

#include "../Action.h"

class Shoot: public Action {
private:
    int weapon;
    int power;
    int angle;

public:
    explicit Shoot(int weapon, int power, int angle);

    int get_weapon();
    int get_power();
    int get_angle();

    char get_send_by(ClientProtocol& prot) override;
};

#endif  // SHOOT_H_
