#include "PlayerConnectedEvent.h"

#include "../EventProcessor/EventProcessor.h"

PlayerConnected::PlayerConnected(const int& player_id): Event(player_id) {}

void PlayerConnected::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_connection(*this);
}

// std::string PlayerConnected::get_player_name() { return this->player_name; }
