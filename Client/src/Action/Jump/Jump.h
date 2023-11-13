#ifndef JUMP_H_
#define JUMP_H_

#include <string>
#include <vector>

#include "../Action.h"

class Jump: public Action {
private:
    bool jump_right;

public:
    explicit Jump(bool is_right);

    char get_send_by(ClientProtocol& prot) override;

    bool is_right();
};

#endif  // JUMP_H_