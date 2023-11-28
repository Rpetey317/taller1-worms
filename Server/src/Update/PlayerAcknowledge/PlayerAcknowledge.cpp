#include "PlayerAcknowledge.h"

#include "ServerProtocol.h"

PlayerAcknowledge::PlayerAcknowledge(const int& _plid): plid(_plid) {}

char PlayerAcknowledge::get_sent_by(ServerProtocol& prot) {
    return prot.send_ConnectionAcknowledgeUpdate(*this);
}

int PlayerAcknowledge::get_plid() const { return this->plid; }
