#ifndef BOX2D_MANAGER
#define BOX2D_MANAGER

#include <cstdio>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "thread.h"
#include "include/box2d/box2d.h"

class BoxSimulator: public Thread {
    Queue<int>& ingoing;  
    Queue<std::vector<float>>& outgoing;
    b2World* world;
    b2Body* worm;
    void initialize_world();

public:
    BoxSimulator(Queue<int>& commands, Queue<std::vector<float>>& positions);
    void run();
    void kill();
};

#endif
