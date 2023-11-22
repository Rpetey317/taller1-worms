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
#include "../../../Common/CommonMapParser/CommonMapParser.h"

#include "box2dPlayer.h"
#include "box2dWorld.h"
#include "ClientUpdateHeaders.h"
#include "GameUpdateHeaders.h"

class BoxSimulator {
    std::list<Box2DPlayer> worms;
    std::list<Box2DPlayer>::iterator playing_worm;
    BoxWorld world;

    // call to function should be implemented in process 
    // but execution in corresponding class
    void next_turn();
    void player_shoot(float angle, float power);
public:
    BoxSimulator();
    bool set_map();
    void add_player(); // should reach agreement whether position is random or sent by server
    GameWorldUpdate* process(ClientBox2DUpdate& update);
};

#endif
