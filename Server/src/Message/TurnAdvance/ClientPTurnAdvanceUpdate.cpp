#include "Game.h"
#include "TurnAdvance.h"

TurnAdvance::TurnAdvance(const int& prev_pl_id, const int& _new_pl_id):
        Message(prev_pl_id), new_pl_id(_new_pl_id) {}

TurnAdvance::~TurnAdvance() {}

bool TurnAdvance::is_valid() { return true; }

std::shared_ptr<Update> TurnAdvance::get_processed_by(Game& game) {
    return game.process_TurnAdvance(*this);
}

const int TurnAdvance::get_new_pl_id() { return this->new_pl_id; }
