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
#include "../../../Common/Vect2D.h"
#include "../../../Common/CommonMapParser/CommonMapParser.h"

#include "../Box2dPlayer/box2dPlayer.h"
#include "../Box2dWorld/box2dWorld.h"
#include "MessageHeaders.h"
#include "UpdateHeaders.h"

class BoxSimulator {
    std::list<Box2DPlayer> worms;
    std::list<Box2DPlayer>::iterator playing_worm;
    BoxWorld world;

    // call to function should be implemented in process 
    // but execution in corresponding class
    void next_turn();
    void player_shoot(float angle, float power);
public:

    std::map<int, Vect2D>* create_position_map(const std::list<Box2DPlayer>& worms);
    Vect2D meter_to_pixel(b2Vec2 meter);

    BoxSimulator();
    bool set_map();
    void add_player(); // should reach agreement whether position is random or sent by server
    std::shared_ptr<WorldUpdate> process(Box2DMsg& update);
};

#endif
