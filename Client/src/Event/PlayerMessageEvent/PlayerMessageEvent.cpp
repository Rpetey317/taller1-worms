#include "PlayerMessageEvent.h"

PlayerMessage::PlayerMessage(const int& _id, const std::string& _msg):
        Event(_id), msg(_msg) {}

std::string PlayerMessage::get_msg() { return this->msg; }
