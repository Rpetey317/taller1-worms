#ifndef STOP_ACTION_H_
#define STOP_ACTION_H_

#include <string>
#include <vector>

#include "../Action.h"

class StopAction: public Action {

public:
    StopAction();

    char get_send_by(ClientProtocol& prot) override;
};

#endif  // STOP_ACTION_H_
