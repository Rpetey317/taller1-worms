#include "box2dContactListener.h"
#include "../../Box2DWeapons/WeaponsHeaders.h"

box2dContactListener::box2dContactListener(Queue<b2Contact*>& contacts) : contacts(contacts) {}

bool box2dContactListener::ReportFixture(b2Fixture* fixture) {
    if(fixture->GetFilterData().categoryBits == WORM)
        foundBodies.push_back( fixture->GetBody() ); 
    return true;
}

void box2dContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    int a = fixtureA->GetFilterData().categoryBits;
    int b = fixtureB->GetFilterData().categoryBits;
    int projectile = BAZOOKA | GREEN_GRANADE | RED_GRANADE | FRAGMENT | AIR_MISSLE | MORTAR | BANANA | HOLY_GRANADE | DYNAMITE;
    if(a != BEAM && b != BEAM) {
        if(a == WORM || b == WORM) {
            if(a & projectile || b & projectile) {
                contacts.push(contact);
            }
        }
    }
}
