#include "ClientUpdate.h"

ClientUpdate::ClientUpdate(std::string const& _msg): msg(_msg), valid(true) {}

std::string ClientUpdate::get_msg() const { return this->msg; }
