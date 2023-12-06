#include "box2dRayCastCallback.h"

box2dRayCastCallback::box2dRayCastCallback() {
    this->body = NULL;
}

float box2dRayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) {
    body = fixture->GetBody();
    this->point = point;
    return fraction;
}
