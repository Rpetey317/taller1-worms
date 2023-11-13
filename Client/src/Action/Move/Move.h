#ifndef MOVE_H_
#define MOVE_H_

#include <string>
#include <vector>

#include "../Action.h"

class Move: public Action {
private:
    bool move_right;

public:
    explicit Move(bool is_right);

    char get_send_by(ClientProtocol& prot) override;

    bool is_right();
};

#endif  // MOVE_H_
