#include "Shoot.h"

#include "../../ClientProtocol/ClientProtocol.h"


Shoot::Shoot(int weapon, int power, int angle): weapon(weapon), power(power), angle(angle) {}

int Shoot::get_weapon() { return this->weapon; }

int Shoot::get_power() { return this->power; }

int Shoot::get_angle() { return this->angle; }

char Shoot::get_send_by(ClientProtocol& prot) { return prot.send_Shoot(*this); }
