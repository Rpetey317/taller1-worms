#ifndef __BOXNULL_H__
#define __BOXNULL_H__

#include "../Box2DMsg.h"

#include "Vect2D.h"

class BoxNull: public Box2DMsg {

public:
    BoxNull(): Box2DMsg(0, 0) {}

    int get_cmd() override{ return COMMAND_NULL; }
};

#endif  // !__BOXNULL_H__
