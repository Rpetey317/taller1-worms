#include "PlayerDisconnectedEvent.h"

#include <iostream>

#include "../EventProcessor/EventProcessor.h"

PlayerDisconnected::PlayerDisconnected(const int& player_id): Event(player_id) {}

void PlayerDisconnected::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_disconnection(*this);
}
