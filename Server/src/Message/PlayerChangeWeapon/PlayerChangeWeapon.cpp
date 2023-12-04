#include "PlayerChangeWeapon.h"

#include <memory>

#include "Game.h"

PlayerChangeWeapon::PlayerChangeWeapon(const int& _id): Message(_id) {}

std::shared_ptr<Update> PlayerChangeWeapon::get_processed_by(Game& game) {
    return game.process_player_change_weapon(*this);
}
