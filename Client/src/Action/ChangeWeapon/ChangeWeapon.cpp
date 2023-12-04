#include "ChangeWeapon.h"

#include "../../ClientProtocol/ClientProtocol.h"

ChangeWeapon::ChangeWeapon(int type_weapon): type_weapon(type_weapon) {}

char ChangeWeapon::get_send_by(ClientProtocol& prot) { return prot.send_ChangeWeapon(*this); }

int ChangeWeapon::get_type_weapon() { return this->type_weapon; }
