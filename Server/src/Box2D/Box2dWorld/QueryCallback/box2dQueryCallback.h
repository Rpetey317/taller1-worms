#ifndef BOX2D_QUERY_CALLBACK_H
#define BOX2D_QUERY_CALLBACK_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include <vector>

class box2dQueryCallback : public b2QueryCallback {
    friend class BoxWorld;
    std::vector<b2Body*> foundBodies;
public:
    bool ReportFixture(b2Fixture* fixture) override;
};

#endif
