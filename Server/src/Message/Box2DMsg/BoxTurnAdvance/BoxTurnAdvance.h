#ifndef __BoxTurnAdvance_H__
#define __BoxTurnAdvance_H__

#include <memory>

#include "../Box2DMsg.h"

class BoxTurnAdvance: public Box2DMsg {

public:
    explicit BoxTurnAdvance(const int& new_pl_id);

    int get_cmd() override;

    ~BoxTurnAdvance();
};

#endif  // !__BoxTurnAdvance_H__
