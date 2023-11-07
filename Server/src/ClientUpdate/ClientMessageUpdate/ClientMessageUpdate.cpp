#include "ClientMessageUpdate.h"
#include "Game.h"

ClientMessageUpdate::ClientMessageUpdate(const int& _id, const std::string& _msg):
        ClientUpdate(_id), msg(_msg) {}

GameUpdate* ClientMessageUpdate::get_processed_by(GameHandler& game) { 
    return game.process_message(*this);
}

std::string& ClientMessageUpdate::get_msg() { return this->msg; }
