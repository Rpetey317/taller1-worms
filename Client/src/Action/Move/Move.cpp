#include "Move.h"

#include "../../ClientProtocol/ClientProtocol.h"

Move::Move(bool is_right): move_right(is_right) {}

char Move::get_send_by(ClientProtocol& prot) { return prot.send_Movement(*this); }

bool Move::is_right() { return this->move_right; }
