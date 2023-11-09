#include "Message.h"


Message::Message(const std::string& msg): msg(msg) {}

char Message::get_send_by(ClientProtocol& prot) { return prot.send_Message(*this); }

std::string Message::get_msg() { return this->msg; }
