#include "ClientConnectedUpdate.h"

#include <memory>

#include "Game.h"

ClientConnectedUpdate::ClientConnectedUpdate(const int& _id): ClientUpdate(_id) {}

std::shared_ptr<GameUpdate> ClientConnectedUpdate::get_processed_by(Game& game) {
    return game.process_new_connect(*this);
}
