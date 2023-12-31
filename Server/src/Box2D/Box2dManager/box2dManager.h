#ifndef BOX2D_MANAGER
#define BOX2D_MANAGER

#include <cstdio>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <memory>

// #include "libs/box2d/include/box2d/box2d.h"

#include "../../../libs/box2d/include/box2d/box2d.h"
#include "../../../Common/queue.h"
#include "../../../Common/thread.h"
#include "../../../Common/Vect2D.h"
#include "../../../Common/Worm.h"
#include "../../../Common/WeaponDTO.h"
#include "../../../Common/CommonConfigurationParser.h"
#include "../../../Common/CommonMapParser/CommonMapParser.h"

#include "../Box2dPlayer/box2dPlayer.h"
#include "../Box2dWorld/box2dWorld.h"
#include "MessageHeaders.h"
#include "UpdateHeaders.h"

class BoxManager {
    std::list<Box2DPlayer> worms;
    std::list<Box2DPlayer>::iterator playing_worm;
    BoxWorld world;
    bool timer_allows;
    CommonConfigurationParser configurator;
    long time_ticker;
    long detonation_tick;
    std::string map_name;
    // call to function should be implemented in process 
    // but execution in corresponding class
    void next_turn(int player_id);
    void player_shoot(int angle, int power, int weapon_type);
    void player_special_shoot(Vect2D position, int weapon_type);
public:

    std::map<int, Worm>* create_position_map(const std::list<Box2DPlayer>& worms);
    std::map<int, WeaponDTO>* create_proyectile_map(const std::list<b2Body*>& projectiles);
  
    Vect2D meter_to_pixel(b2Vec2 meter, float offset_x, float offset_y);

    explicit BoxManager(std::string file_name);
    bool set_map(std::string file_name);
    void tick();
    void fire_projectile(float angle, float power, float restitution, int category, int mask, bool set_timer, int type);
    void air_strike(Vect2D position);
    void teleport(Vect2D position);
    void dynamite(float restitution, int category, int mask);
    void baseball_bat(float angle, float power);
    void set_teams(int worm_id, int player_id);
    std::shared_ptr<WorldUpdate> process(std::shared_ptr<Box2DMsg> update);
};

#endif
