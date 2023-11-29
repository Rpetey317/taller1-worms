#include "TurnChange.h"

#include "ServerProtocol.h"

TurnChange::TurnChange(const int& _new_curr_player): new_curr_player(_new_curr_player) {}

char TurnChange::get_sent_by(ServerProtocol& prot) { return prot.send_TurnChangeUpdate(*this); }

const int& TurnChange::get_new_curr_player() const { return this->new_curr_player; }
