#ifndef BOX2D_CONTACTLISTENER_H
#define BOX2D_CONTACTLISTENER_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../../../Common/queue.h"
#include <vector>

class box2dContactListener : public b2ContactListener {
    friend class BoxWorld;
    std::vector<b2Body*> foundBodies;
    Queue<b2Contact*>& contacts;
    explicit box2dContactListener(Queue<b2Contact*>& contacts);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
    
    bool ReportFixture(b2Fixture* fixture);
};

#endif
