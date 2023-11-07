#include "ConnectionAcknowledgeUpdate.h"

#include "ServerProtocol.h"

ConnectionAcknowledgeUpdate::ConnectionAcknowledgeUpdate(int& _plid): plid(_plid) {}

char ConnectionAcknowledgeUpdate::get_sent_by(ServerProtocol& prot) {
    return prot.send_ConnectionAcknowledgeUpdate(*this);
}

const int& ConnectionAcknowledgeUpdate::get_plid() const { return this->plid; }
