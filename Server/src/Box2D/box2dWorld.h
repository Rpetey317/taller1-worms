#ifndef BOX2D_WORLD_H
#define BOX2D_WORLD_H

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../../../Common/CommonMapParser/CommonMapParser.h"
#include "../../../Common/Vect2D.h"

#include <cstdio>
#include <vector>
#include <list>
#include <vector>

#define WORM_HALF_WIDTH 0.12f
#define WORM_HALF_HEIGHT 0.15f

class BoxWorld {
    friend class BoxSimulator;
    BoxWorld();
    b2World* world;
    void initialize_world();
    b2Body* create_worm(float x, float y);
    void create_ground(b2Vec2 lower_l, b2Vec2 lower_r, b2Vec2 upper_l, b2Vec2 upper_r);
    void create_wall(b2Vec2 start, b2Vec2 end);
    void create_long_beam(b2Vec2 start, float angle);
    void create_short_beam(b2Vec2 start, float angle);
    void step();
    bool set_map(std::vector<Tile> map); 
    b2Vec2 pixel_to_meter(Vect2D pixel);
};

#endif
