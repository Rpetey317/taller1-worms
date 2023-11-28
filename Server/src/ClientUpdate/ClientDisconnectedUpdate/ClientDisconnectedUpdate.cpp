#include "ClientDisconnectedUpdate.h"

#include "Game.h"

ClientDisconnectedUpdate::ClientDisconnectedUpdate(const int& _id): ClientUpdate(_id) {}

std::shared_ptr<GameUpdate> ClientDisconnectedUpdate::get_processed_by(GameHandler& game) {
    return game.process_disconnect(*this);
}
