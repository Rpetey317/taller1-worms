#ifndef __BoxTurnAdvance_H__
#define __BoxTurnAdvance_H__

#include "../Box2DMsg.h"

#include <memory>

class BoxTurnAdvance: public Box2DMsg {

public:
    BoxTurnAdvance(const int& new_pl_id);

    int get_cmd() override;

    ~BoxTurnAdvance();
};

#endif // !__BoxTurnAdvance_H__
