#ifndef JUMP_H_
#define JUMP_H_

#include <string>
#include <vector>

#include "../Action.h"

class Jump: public Action {
private:
    bool jump_forward;

public:
    explicit Jump(bool is_forward);

    char get_send_by(ClientProtocol& prot) override;

    bool is_forward();
};

#endif  // JUMP_H_
