#include "PlayerDisconnectedEvent.h"

#include <iostream>

#include "../EventProcessor/EventProcessor.h"

PlayerDisconnected::PlayerDisconnected(const int& player_id): Event(player_id) {}

void PlayerDisconnected::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_disconnection(*this);
}

std::map<int, Vect2D> PlayerDisconnected::get_worm_positions() { return std::map<int, Vect2D>(); }

bool PlayerDisconnected::is_new_player() { return false; }

// std::string PlayerDisconnected::get_player_name() { return this->player_name; }
