#include "GameAcknowledgeUpdate.h"

#include "ServerProtocol.h"

GameAcknowledgeUpdate::GameAcknowledgeUpdate(const int& _plid): plid(_plid) {}

char GameAcknowledgeUpdate::get_sent_by(ServerProtocol& prot) {
    return prot.send_ConnectionAcknowledgeUpdate(*this);
}

const int& GameAcknowledgeUpdate::get_plid() const { return this->plid; }
