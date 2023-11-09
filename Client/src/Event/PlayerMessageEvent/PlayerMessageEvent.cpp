#include "PlayerMessageEvent.h"

#include "../EventProcessor/EventProcessor.h"

PlayerMessage::PlayerMessage(const int& _id, const std::string& _msg): Event(_id), msg(_msg) {}

void PlayerMessage::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_msg(*this);
}

std::string PlayerMessage::get_msg() { return this->msg; }
