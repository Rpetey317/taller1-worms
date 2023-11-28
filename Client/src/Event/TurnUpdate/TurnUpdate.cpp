#include "TurnUpdate.h"

#include <map>

#include "../EventProcessor/EventProcessor.h"

TurnUpdate::TurnUpdate(const int& player_id): Event(player_id) {}

void TurnUpdate::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_turn_update(*this);
}

std::map<int, Vect2D> TurnUpdate::get_worm_positions() { return std::map<int, Vect2D>(); }

std::map<int, Worm> TurnUpdate::get_worms() { return std::map<int, Worm>(); }

bool TurnUpdate::is_new_player() { return false; }
