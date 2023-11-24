#include "ClientNullUpdate.h"

#include "Game.h"

ClientNullUpdate::ClientNullUpdate(): ClientUpdate(-1) {}

ClientNullUpdate::~ClientNullUpdate() = default;

bool ClientNullUpdate::is_valid() { return false; }

GameUpdate* ClientNullUpdate::get_processed_by(GameHandler& game) {
    return game.process_NullUpdate(*this);
}
