#include "GameNullUpdate.h"

#include "ServerProtocol.h"

char GameNullUpdate::get_sent_by(ServerProtocol& prot) { return prot.send_NullUpdate(*this); }
