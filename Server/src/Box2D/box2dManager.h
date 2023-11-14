#ifndef BOX2D_MANAGER
#define BOX2D_MANAGER

#include <cstdio>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

// #include "libs/box2d/include/box2d/box2d.h"

#include "../../../libs/box2d/include/box2d/box2d.h"

// #include "queue.h"
// #include "thread.h"
#include "../../../Common/queue.h"
#include "../../../Common/thread.h"

class BoxSimulator: public Thread {
    Queue<int>& ingoing;
    Queue<std::vector<int>>& outgoing;
    b2World* world;
    b2Body* worm;
    void initialize_world();

public:
    BoxSimulator(Queue<int>& commands, Queue<std::vector<int>>& positions);
    void run();
    void kill();
};

#endif
