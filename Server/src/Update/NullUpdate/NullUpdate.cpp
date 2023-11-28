#include "NullUpdate.h"

#include "ServerProtocol.h"

char NullUpdate::get_sent_by(ServerProtocol& prot) { return prot.send_NullUpdate(*this); }
