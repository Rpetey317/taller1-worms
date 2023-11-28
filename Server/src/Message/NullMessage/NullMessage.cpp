#include "NullMessage.h"

#include <memory>

#include "Game.h"

NullMessage::NullMessage(): Message(-1) {}

NullMessage::~NullMessage() = default;

bool NullMessage::is_valid() { return false; }

std::shared_ptr<GameUpdate> NullMessage::get_processed_by(Game& game) {
    return game.process_NullUpdate(*this);
}
