#ifndef BOX2D_PLAYER
#define BOX2D_PLAYER

#include "../../../libs/box2d/include/box2d/box2d.h"

class Box2DPlayer {
    int id;
    b2Body* body;
    int health_points;
    int direction;
    int state;
    
    public:
    Box2DPlayer(int id, b2Body* body, int direction, int state);
    Box2DPlayer(int id, b2Body* body);
    b2Body* get_body();
    int get_id();
    void get_hurt(int damage);
    void kill();
    void set_direction(int direction);
    int get_direction();
    void set_health_points(int health_points);
    int get_health_points();
    void set_state(int state);
    int get_state();
    bool is_alive();
};

#endif
