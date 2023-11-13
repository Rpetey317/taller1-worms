#include "PlayerPosition.h"

#include "../EventProcessor/EventProcessor.h"

PlayerPosition::PlayerPosition(const int& player_id, const int& pos_x, const int& pos_y): Event(player_id), pos_x(pos_x), pos_y(pos_y) {}

void PlayerPosition::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_player_position(*this);
}

int PlayerPosition::get_position_x() { return this->pos_x; }

int PlayerPosition::get_position_y() { return this->pos_y; }
