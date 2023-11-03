#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <vector>

//#include "../ServerProtocol/ServerProtocol.h"
class ServerProtocol;

class Action {

public:
    std::string msg;  // to be removed
    Action();
    Action(std::string msg);
    std::string get_msg();
    ~Action();
};

#endif  // ACTION_H_