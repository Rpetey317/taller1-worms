#include "box2dQueryCallback.h"

#include "../../Box2DWeapons/Weapons.h"

bool MyQueryCallback::ReportFixture(b2Fixture* fixture) {
    if(fixture->GetFilterData().categoryBits == WORM)
        foundBodies.push_back( fixture->GetBody() ); 
    return true;
}