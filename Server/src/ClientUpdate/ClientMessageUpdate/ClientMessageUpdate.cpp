#include "ClientMessageUpdate.h"

#include <memory>

#include "Game.h"

ClientMessageUpdate::ClientMessageUpdate(const int& _id, const std::string& _msg):
        ClientUpdate(_id), msg(_msg) {}

std::shared_ptr<GameUpdate> ClientMessageUpdate::get_processed_by(Game& game) {
    return game.process_message(*this);
}

std::string& ClientMessageUpdate::get_msg() { return this->msg; }
