#ifndef BOX2D_WORLD_H
#define BOX2D_WORLD_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../../../Common/CommonMapParser/CommonMapParser.h"
#include "../../../Common/Vect2D.h"
#include "../../../Common/queue.h"
#include "../../../Common/Worm.h"
#include "../../../Common/CommonConfigurationParser.h"
#include "ContactListener/box2dContactListener.h"
#include "QueryCallback/box2dQueryCallback.h"
#include "RayCastCallback/box2dRayCastCallback.h"
#include "../Box2dPlayer/box2dPlayer.h"
#include <cstdio>
#include <vector>
#include <list>
#include <vector>

#define WORM_HALF_WIDTH 0.12f
#define WORM_HALF_HEIGHT 0.15f

class BoxWorld {
    friend class BoxManager;

    CommonConfigurationParser configurator;
    BoxWorld(std::list<Box2DPlayer>& worm);
    std::list<Box2DPlayer>& worms;
    Queue<b2Contact*> contacts;
    b2World* world;
    void initialize_world();
    bool set_map(std::vector<Tile> map); 

    b2Body* create_worm(float x, float y, int id);
    void create_ground(b2Vec2 lower_l, b2Vec2 lower_r, b2Vec2 upper_l, b2Vec2 upper_r);
    void create_wall(b2Vec2 start, b2Vec2 end);
    void create_long_beam(b2Vec2 start, float angle);
    void create_short_beam(b2Vec2 start, float angle);
    
    box2dContactListener* contact_listener;
    void step();
    void set_teams(int worm_id, int player_id);

    bool check_blast;
    bool create_fragments;
    bool air_check;
    bool timer_allows;
    int fragment_amount;
    float fragment_radius;
    float fragment_damage;
    std::list <b2Body*> projectiles;
    std::list <b2Body*> projectiles_to_remove;
    b2Vec2 contactCenter;
    float blastRadius;
    float blastPower;
    b2Body* create_projectile(float x, float y, float restitution, float direction, int category, int mask, bool set_timer, int type);
    void contactSolver(b2Contact* contact, float radius, float power,  b2Fixture* fixture);  
    void PostSolve();
    void execute_checks();
    void fragments();
    void air_strike(Vect2D position);
    void teleport(Vect2D position, b2Body* current);
    void air_missiles();
    void blast();
    void dynamite(b2Vec2 position);
    void clean_projectiles(bool full_clean);
    void baseball_bat(b2Body* current, float angle, float power, float direction);

    b2Vec2 pixel_to_meter(Vect2D pixel);
    ~BoxWorld();
};

#endif
