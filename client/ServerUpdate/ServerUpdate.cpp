#include "ServerUpdate.h"

ClientUpdate::ClientUpdate(std::string const& _msg): msg(_msg) {}

std::string ClientUpdate::get_msg() const { return this->msg; }
