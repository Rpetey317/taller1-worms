#include "PlayerPosition.h"

#include <map>

#include "../EventProcessor/EventProcessor.h"

PlayerPosition::PlayerPosition(const int& player_id, Vect2D position):
        Event(player_id), position(position) {}

void PlayerPosition::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_player_position(*this);
}

// Vect2D PlayerPosition::get_position() { return this->position; }
