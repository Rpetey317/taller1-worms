#include "box2dPlayer.h"

Box2DPlayer::Box2DPlayer(int id, b2Body* body){
    this->id = id;
    this->body = body;
    this->health_points = 100;
}
b2Body* Box2DPlayer::get_body(){
    return body;
}
int Box2DPlayer::get_id(){
    return id;
}

void Box2DPlayer::get_hurt(int damage){
    if (damage > this->health_points)
        this->kill();
    else
        this->health_points -= damage;
}

void Box2DPlayer::kill(){
    this->health_points = 0;
}
