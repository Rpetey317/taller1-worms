#include "PlayerConnected.h"

#include <memory>

#include "Game.h"

PlayerConnected::PlayerConnected(const int& _id): Message(_id) {}

std::shared_ptr<GameUpdate> PlayerConnected::get_processed_by(Game& game) {
    return game.process_new_connect(*this);
}
