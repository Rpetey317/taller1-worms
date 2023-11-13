#include "Jump.h"

#include "../../ClientProtocol/ClientProtocol.h"

Jump::Jump(bool is_right): jump_right(is_right) {}

char Jump::get_send_by(ClientProtocol& prot) { return prot.send_Jump(*this); }

bool Jump::is_right() { return this->jump_right; }
