#include "TurnChangeUpdate.h"

#include "ServerProtocol.h"

TurnChangeUpdate::TurnChangeUpdate(int& _new_curr_player): new_curr_player(_new_curr_player) {}

char TurnChangeUpdate::get_sent_by(ServerProtocol& prot) {
    return prot.send_TurnChangeUpdate(*this);
}

const int& TurnChangeUpdate::get_new_curr_player() const { return this->new_curr_player; }
