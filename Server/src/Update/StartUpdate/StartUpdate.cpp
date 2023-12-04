#include "StartUpdate.h"

#include "ServerProtocol.h"

StartUpdate::StartUpdate() {}

char StartUpdate::get_sent_by(ServerProtocol& prot) {
    return prot.send_Start(*this);
}

StartUpdate::~StartUpdate() {}
