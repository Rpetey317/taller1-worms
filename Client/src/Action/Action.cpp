#include "Action.h"


Action::Action(): type_action(0), msg("") {}

Action::Action(msgcode_t type_action, std::string msg): type_action(type_action), msg(msg) {}

std::string Action::get_msg() { return this->msg; }

Action::~Action() {}
