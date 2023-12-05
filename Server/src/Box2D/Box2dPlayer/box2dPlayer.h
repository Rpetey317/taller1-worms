#ifndef BOX2D_PLAYER
#define BOX2D_PLAYER

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../../../Common/Worm.h"

class Box2DPlayer {
    int id;
    b2Body* body;
    int health_points;
    int direction;
    int state;
    int team_id;
    
    public:
    Box2DPlayer(int id, b2Body* body, int direction, int state, int health_points);
    Box2DPlayer(int id, b2Body* body);
    b2Body* get_body();
    int get_id();
    void get_hurt(int damage);
    void kill();
    void set_direction(int direction);
    void set_id(int id);
    int get_direction();
    void set_health_points(int health_points);
    int get_health_points();
    void set_state(int state);
    int get_state();
    void set_team_id(int team_id);
    int get_team_id();
    bool is_alive();
    bool is_falling();
};

#endif
