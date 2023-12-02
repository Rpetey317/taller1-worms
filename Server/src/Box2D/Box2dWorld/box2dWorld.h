#ifndef BOX2D_WORLD_H
#define BOX2D_WORLD_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../../../Common/CommonMapParser/CommonMapParser.h"
#include "../../../Common/Vect2D.h"
#include "../../../Common/queue.h"
// #include "../Box2DWeapons/WeaponsHeaders.h"
#include "ContactListener/box2dContactListener.h"
#include "QueryCallback/box2dQueryCallback.h"

#include <cstdio>
#include <vector>
#include <list>
#include <vector>

#define WORM_HALF_WIDTH 0.12f
#define WORM_HALF_HEIGHT 0.15f

class BoxWorld {
    friend class BoxManager;

    BoxWorld();
    Queue<b2Contact*> contacts;
    b2World* world;
    void initialize_world();
    bool set_map(std::vector<Tile> map); 

    b2Body* create_worm(float x, float y);
    void create_ground(b2Vec2 lower_l, b2Vec2 lower_r, b2Vec2 upper_l, b2Vec2 upper_r);
    void create_wall(b2Vec2 start, b2Vec2 end);
    void create_long_beam(b2Vec2 start, float angle);
    void create_short_beam(b2Vec2 start, float angle);
    
    box2dContactListener* contact_listener;
    void step();

    bool check_blast;
    bool create_fragments;
    bool air_check;
    bool check_teleport;
    std::list <b2Body*> projectiles;
    std::list <b2Body*> projectiles_to_remove;
    b2Vec2 contactCenter;
    float blastRadius;
    float blastPower;
    b2Body* create_projectile(float x, float y, float restitution, float direction, int category, int mask);
    void contactSolver(b2Contact* contact, float radius, float power,  b2Fixture* fixture);  
    void PostSolve();
    void execute_checks();
    void fragments();
    void air_missiles();
    void clean_projectiles();

    b2Vec2 pixel_to_meter(Vect2D pixel);
    ~BoxWorld();
};

#endif
