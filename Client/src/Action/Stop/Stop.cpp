#include "Stop.h"

#include "../../ClientProtocol/ClientProtocol.h"

StopAction::StopAction() {}

char StopAction::get_send_by(ClientProtocol& prot) { return prot.send_Stop(*this); }
