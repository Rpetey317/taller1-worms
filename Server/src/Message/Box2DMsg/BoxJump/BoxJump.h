#ifndef __BOXJUMP_H__
#define __BOXJUMP_H__

#include <memory>

#include "../Box2DMsg.h"

class BoxJump: public Box2DMsg {
    bool forward;

    BoxJump(bool is_forward, int id);

public:
    static std::shared_ptr<Message> jump_fw(int id);
    static std::shared_ptr<Message> jump_bw(int id);

    int get_cmd() override;

    bool is_forward() const;
};

#endif  // !__BOXJUMP_H__
