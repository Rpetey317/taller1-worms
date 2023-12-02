#include "PlayerConnectedEvent.h"

#include <map>

#include "../EventProcessor/EventProcessor.h"

PlayerConnected::PlayerConnected(const int& player_id): Event(player_id) {}

void PlayerConnected::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_connection(*this);
}

bool PlayerConnected::is_new_player() { return true; }
