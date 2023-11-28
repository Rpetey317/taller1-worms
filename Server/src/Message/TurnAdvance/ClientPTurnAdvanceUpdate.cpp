#include "Game.h"
#include "TurnAdvance.h"

TurnAdvance::TurnAdvance(const int& prev_pl_id,
                         const std::map<int, std::unique_ptr<PlayerHandler>>::iterator& _new_pl):
        Message(prev_pl_id), new_pl(_new_pl) {}

TurnAdvance::~TurnAdvance() {}

bool TurnAdvance::is_valid() { return true; }

std::shared_ptr<Update> TurnAdvance::get_processed_by(Game& game) {
    return game.process_TurnAdvance(*this);
}

const std::map<int, std::unique_ptr<PlayerHandler>>::iterator& TurnAdvance::get_new_pl() {
    return this->new_pl;
}
