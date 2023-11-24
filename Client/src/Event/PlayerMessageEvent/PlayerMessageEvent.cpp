#include "PlayerMessageEvent.h"

#include "../EventProcessor/EventProcessor.h"

PlayerMessage::PlayerMessage(const int& _id, const std::string& _msg): Event(_id), msg(_msg) {}

void PlayerMessage::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_msg(*this);
}

std::map<int, Vect2D> PlayerMessage::get_worm_positions() { return std::map<int, Vect2D>(); }

std::map<int, Worm> PlayerMessage::get_worms() { return std::map<int, Worm>(); }

bool PlayerMessage::is_new_player() { return false; }

std::string PlayerMessage::get_msg() { return this->msg; }
