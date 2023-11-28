#include "Chat.h"

#include <memory>

#include "Game.h"

Chat::Chat(const int& _id, const std::string& _msg): Message(_id), msg(_msg) {}

std::shared_ptr<Update> Chat::get_processed_by(Game& game) { return game.process_message(*this); }

std::string& Chat::get_msg() { return this->msg; }
