#ifndef NULL_ACTION_H_
#define NULL_ACTION_H_

#include <string>
#include <vector>

#include "../Action.h"

class NullAction: public Action {

public:
        NullAction();

    char get_send_by(ClientProtocol& prot) override;
};

#endif  // NULL_ACTION_H_
