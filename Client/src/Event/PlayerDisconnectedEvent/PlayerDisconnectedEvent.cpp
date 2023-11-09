#include "PlayerDisconnectedEvent.h"

#include "../EventProcessor/EventProcessor.h"

PlayerDisconnected::PlayerDisconnected(const int& player_id): Event(player_id) {}

void PlayerDisconnected::get_processed_by(EventProcessor & eventProcessor) {
    eventProcessor.process_disconnection(*this);
}

// std::string PlayerDisconnected::get_player_name() { return this->player_name; }
