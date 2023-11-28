#include "ClientBox2DUpdate.h"

#include <memory>

#include "Game.h"

ClientBox2DUpdate::ClientBox2DUpdate(const int& _id, const int& _cmd):
        ClientUpdate(_id), command(_cmd) {}

std::shared_ptr<GameUpdate> ClientBox2DUpdate::get_processed_by(GameHandler& game) {
    return game.process_box2d(*this);
}

int& ClientBox2DUpdate::get_cmd() { return this->command; }
