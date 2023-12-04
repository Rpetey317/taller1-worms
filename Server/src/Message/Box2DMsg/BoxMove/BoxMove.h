#ifndef __BOXMOVE_H__
#define __BOXMOVE_H__

#include <memory>

#include "../Box2DMsg.h"

class BoxMove: public Box2DMsg {
    bool right;

    BoxMove(bool is_right, int id);

public:
    static std::shared_ptr<Message> move_right(int id);
    static std::shared_ptr<Message> move_left(int id);

    int get_cmd() override;

    bool is_right() const;
};

#endif  // !__BOXMOVE_H__
