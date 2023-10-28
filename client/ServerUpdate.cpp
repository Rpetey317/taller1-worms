#include "ServerUpdate.h"

ServerUpdate::ServerUpdate(std::string const& _msg): msg(_msg) {}

std::string ServerUpdate::get_msg() const {
    return this->msg;
}
