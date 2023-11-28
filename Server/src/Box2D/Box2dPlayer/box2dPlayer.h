#ifndef BOX2D_PLAYER
#define BOX2D_PLAYER

#include "../../../libs/box2d/include/box2d/box2d.h"

class Box2DPlayer {
    int id;
    b2Body* body;

    public:
    Box2DPlayer(int id, b2Body* body){
        this->id = id;
        this->body = body;
    }
    b2Body* get_body(){
        return body;
    }
    int get_id(){
        return id;
    }
};

#endif
