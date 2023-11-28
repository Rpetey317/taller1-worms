#include "PlayerDisconnectedMessage.h"

#include <memory>

#include "Game.h"

PlayerDisconnectedMessage::PlayerDisconnectedMessage(const int& _id): Message(_id) {}

std::shared_ptr<Update> PlayerDisconnectedMessage::get_processed_by(Game& game) {
    return game.process_disconnect(*this);
}
