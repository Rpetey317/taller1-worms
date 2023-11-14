#include "ClientConnectedUpdate.h"

#include "Game.h"

ClientConnectedUpdate::ClientConnectedUpdate(const int& _id): ClientUpdate(_id) {}

GameUpdate* ClientConnectedUpdate::get_processed_by(GameHandler& game) {
    return game.process_new_connect(*this);
}
