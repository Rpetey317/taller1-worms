#include "PlayerConnectedEvent.h"

#include "../EventProcessor/EventProcessor.h"

PlayerConnected::PlayerConnected(const int& player_id): Event(player_id) {}

void PlayerConnected::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_connection(*this);
}

std::map<int, Vect2D> PlayerConnected::get_worm_positions() { return std::map<int, Vect2D>(); }

// std::string PlayerConnected::get_player_name() { return this->player_name; }
