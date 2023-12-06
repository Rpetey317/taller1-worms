#ifndef __BOXSTOP_H__
#define __BOXSTOP_H__

#include "../Box2DMsg.h"

#include "Vect2D.h"

class BoxStop: public Box2DMsg {

public:
        BoxStop(int _id);
    int get_cmd() override { return COMMAND_STOP_MOVING; }
};

#endif  // !__BOXSTOP_H__
