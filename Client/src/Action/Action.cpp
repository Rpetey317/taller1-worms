#include "Action.h"


Action::Action(): msg("") {}

Action::Action(std::string msg): msg(msg) {}

std::string Action::get_msg() { return this->msg; }

Action::~Action() {}
