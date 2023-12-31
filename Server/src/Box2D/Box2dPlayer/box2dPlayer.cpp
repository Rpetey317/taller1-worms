#include "box2dPlayer.h"

Box2DPlayer::Box2DPlayer(int id, b2Body* body, int direction, int state, int health_points): id(id), body(body), health_points(health_points), direction(direction), state(state) {}

Box2DPlayer::Box2DPlayer(int id, b2Body* body): id(id), body(body), health_points(-1), direction(0), state(0) {}

b2Body* Box2DPlayer::get_body(){
    return body;
}

int Box2DPlayer::get_id(){
    return id;
}

void Box2DPlayer::set_direction(int direction){
    this->direction = direction;
}

int Box2DPlayer::get_direction(){
    return this->direction;
}

bool Box2DPlayer::is_alive(){
    return health_points > 0;
}

void Box2DPlayer::get_hurt(int damage){
    if (damage > this->health_points)
        this->kill();
    else
        this->health_points -= damage;
}

void Box2DPlayer::set_health_points(int health_points){
    this->health_points = health_points;
}

int Box2DPlayer::get_health_points(){
    return this->health_points;
}

void Box2DPlayer::set_state(int state){
    this->state = state;
}

int Box2DPlayer::get_state(){
    return this->state;
}

void Box2DPlayer::kill(){
    this->health_points = 0;
    this->set_state(WORM_DEAD);
}

bool Box2DPlayer::is_falling(){
    return this->body->GetLinearVelocity().y < -0.01f;
}

void Box2DPlayer::set_team_id(int team_id){
    this->team_id = team_id;
}

int Box2DPlayer::get_team_id(){
    return this->team_id;
}
