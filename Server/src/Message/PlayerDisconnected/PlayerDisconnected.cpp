#include "PlayerDisconnected.h"

#include <memory>

#include "Game.h"

PlayerDisconnected::PlayerDisconnected(const int& _id): Message(_id) {}

std::shared_ptr<GameUpdate> PlayerDisconnected::get_processed_by(Game& game) {
    return game.process_disconnect(*this);
}
