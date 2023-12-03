#ifndef BOX2D_PLAYER
#define BOX2D_PLAYER

#include "../../../libs/box2d/include/box2d/box2d.h"

class Box2DPlayer {
    int id;
    b2Body* body;
    int health_points;
    
    public:
    Box2DPlayer(int id, b2Body* body);
    b2Body* get_body();
    int get_id();
    void get_hurt(int damage);
    void kill();
};

#endif
