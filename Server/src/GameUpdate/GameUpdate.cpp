#include "Server/src/GameUpdate/GameUpdate.h"

GameUpdate::GameUpdate(std::string const& _msg): msg(_msg) {}

std::string GameUpdate::get_msg() const { return this->msg; }
