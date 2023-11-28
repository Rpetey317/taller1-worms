#include "ClientPTurnAdvanceUpdate.h"

#include "Game.h"

ClientPTurnAdvanceUpdate::ClientPTurnAdvanceUpdate(
        const int& prev_pl_id,
        const std::map<int, std::unique_ptr<PlayerHandler>>::iterator& _new_pl):
        ClientUpdate(prev_pl_id), new_pl(_new_pl) {}

ClientPTurnAdvanceUpdate::~ClientPTurnAdvanceUpdate() {}

bool ClientPTurnAdvanceUpdate::is_valid() { return true; }

std::shared_ptr<GameUpdate> ClientPTurnAdvanceUpdate::get_processed_by(GameHandler& game) {
    return game.process_TurnAdvance(*this);
}

const std::map<int, std::unique_ptr<PlayerHandler>>::iterator&
        ClientPTurnAdvanceUpdate::get_new_pl() {
    return this->new_pl;
}
