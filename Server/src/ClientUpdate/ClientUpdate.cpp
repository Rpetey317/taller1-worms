#include "ClientUpdate.h"

ClientUpdate::ClientUpdate(std::string const& _msg, const int& _id):
        msg(_msg), id(_id), valid(true) {}

std::string ClientUpdate::get_msg() const { return this->msg; }
