#include "PlayerPosition.h"

#include "../EventProcessor/EventProcessor.h"

PlayerPosition::PlayerPosition(const int& player_id, Point position):
        Event(player_id), position(position) {}

void PlayerPosition::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_player_position(*this);
}

Point PlayerPosition::get_position() { return this->position; }
