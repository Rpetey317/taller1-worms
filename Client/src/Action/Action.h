#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <vector>

#include "NetworkProtocol.h"

using NetworkProtocol::msgcode_t;

class Action {

public:
    msgcode_t type_action;
    size_t code_game;
    std::string msg;  // to be removed
    Action();
    Action(msgcode_t type_action, std::string msg);
    std::string get_msg();
    ~Action();
};

#endif  // ACTION_H_
