#include "NullAction.h"

#include "../../ClientProtocol/ClientProtocol.h"

NullAction::NullAction(){}

char NullAction::get_send_by(ClientProtocol& prot) { return prot.send_NullAction(*this); }

