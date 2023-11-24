#include "TurnUpdate.h"

#include "../EventProcessor/EventProcessor.h"

TurnUpdate::TurnUpdate(const int& player_id): Event(player_id) {}

void TurnUpdate::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_turn_update(*this);
}

std::map<int, Vect2D> TurnUpdate::get_worm_positions() { return std::map<int, Vect2D>(); }

bool TurnUpdate::is_new_player() { return false; }
