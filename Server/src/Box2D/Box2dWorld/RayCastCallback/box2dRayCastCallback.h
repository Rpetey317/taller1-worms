#ifndef RAYCAST_CALL_BACK_H
#define RAYCAST_CALL_BACK_H

#include "../../../libs/box2d/include/box2d/box2d.h"

class box2dRayCastCallback : public b2RayCastCallback {
public:
    box2dRayCastCallback ();
    b2Body* body;
    b2Vec2 point;

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction);
};

#endif
