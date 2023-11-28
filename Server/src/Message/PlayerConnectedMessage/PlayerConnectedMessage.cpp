#include "PlayerConnectedMessage.h"

#include <memory>

#include "Game.h"

PlayerConnectedMessage::PlayerConnectedMessage(const int& _id): Message(_id) {}

std::shared_ptr<Update> PlayerConnectedMessage::get_processed_by(Game& game) {
    return game.process_new_connect(*this);
}
