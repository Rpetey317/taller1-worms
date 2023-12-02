#include "RunTimer.h"

#include <memory>

#include "Game.h"

RunTimer::RunTimer(int _id): Message(_id) {}

std::shared_ptr<Update> RunTimer::get_processed_by(Game& game) {
    return game.process_timer(*this);
}
