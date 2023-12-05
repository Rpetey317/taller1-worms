#include "BoxChangeWeapon.h"

BoxChangeWeapon::BoxChangeWeapon(int plid, int weapon_id): Box2DMsg(plid, 0), weapon_id(weapon_id) {}

int BoxChangeWeapon::get_cmd() { return COMMAND_CHANGE_WP; }

int BoxChangeWeapon::get_weapon_id() const { return this->weapon_id; }

BoxChangeWeapon::~BoxChangeWeapon() {}
