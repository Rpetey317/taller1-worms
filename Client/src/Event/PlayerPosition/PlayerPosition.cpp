#include "PlayerPosition.h"

#include <map>

#include "../EventProcessor/EventProcessor.h"

PlayerPosition::PlayerPosition(const int& player_id, Vect2D position):
        Event(player_id), position(position) {}

void PlayerPosition::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_player_position(*this);
}

std::map<int, Vect2D> PlayerPosition::get_worm_positions() { return std::map<int, Vect2D>(); }

bool PlayerPosition::is_new_player() { return false; }

Vect2D PlayerPosition::get_position() { return this->position; }
