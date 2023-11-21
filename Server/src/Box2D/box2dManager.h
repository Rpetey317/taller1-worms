#ifndef BOX2D_MANAGER
#define BOX2D_MANAGER

#include <cstdio>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>

// #include "libs/box2d/include/box2d/box2d.h"

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../../../Common/queue.h"
#include "../../../Common/thread.h"
#include "../../../Common/Point.h"



#include "box2dPlayer.h"
#include "ClientUpdateHeaders.h"
#include "GameUpdateHeaders.h"

class BoxSimulator {
    Queue<int>& ingoing;

    Queue<std::vector<int>>& outgoing;
    b2World* world;
    std::list<Box2DPlayer> worms;
    std::list<Box2DPlayer>::iterator playing_worm;
    void initialize_world();
    b2Body* create_worm(float x, float y);
    void create_ground(b2Vec2 lower_l, b2Vec2 lower_r, b2Vec2 upper_l, b2Vec2 upper_r);
    void create_wall(b2Vec2 start, b2Vec2 end);
    void create_long_beam(b2Vec2 start, float angle);
    void create_short_beam(b2Vec2 start, float angle);
    void next_turn();
    void add_player(); // should reach agreement whether position is random or sent by server

    // might fall into player subclass
    void player_shoot(float angle, float power);
public:
    BoxSimulator(Queue<int>& commands, Queue<std::vector<int>>& positions);

    // 
    // void run();

    // add_player
    //
    GameWorldUpdate* process(ClientBox2DUpdate& update);

    void kill();
};

#endif
