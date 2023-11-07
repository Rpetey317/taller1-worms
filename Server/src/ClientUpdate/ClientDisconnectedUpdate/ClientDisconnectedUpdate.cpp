#include "ClientDisconnectedUpdate.h"

#include "Game.h"

ClientDisconnectedUpdate::ClientDisconnectedUpdate(const int& _id): ClientUpdate(_id) {}

GameUpdate* ClientDisconnectedUpdate::get_processed_by(GameHandler& game) {
    return game.process_disconnect(*this);
}
