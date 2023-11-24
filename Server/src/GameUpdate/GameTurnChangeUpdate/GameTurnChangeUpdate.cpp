#include "GameTurnChangeUpdate.h"

#include "ServerProtocol.h"

GameTurnChangeUpdate::GameTurnChangeUpdate(const int& _new_curr_player):
        new_curr_player(_new_curr_player) {}

char GameTurnChangeUpdate::get_sent_by(ServerProtocol& prot) {
    return prot.send_TurnChangeUpdate(*this);
}

const int& GameTurnChangeUpdate::get_new_curr_player() const { return this->new_curr_player; }
