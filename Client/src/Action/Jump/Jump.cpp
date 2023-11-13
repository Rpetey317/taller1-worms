#include "Jump.h"

#include "../../ClientProtocol/ClientProtocol.h"

Jump::Jump(bool is_forward): jump_forward(is_forward) {}

char Jump::get_send_by(ClientProtocol& prot) { return prot.send_Jump(*this); }

bool Jump::is_forward() { return this->jump_forward; }
