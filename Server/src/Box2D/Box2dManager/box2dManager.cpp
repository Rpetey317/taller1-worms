#include "box2dManager.h"
#include "Vect2D.h"
#include <iostream>
#include "../Box2DWeapons/WeaponsHeaders.h"
#include "Box2DMsg/Box2DMsgHeaders.h"

#define DEGTORAD -0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define LEFT 1
#define RIGHT 0

Vect2D BoxManager::meter_to_pixel(b2Vec2 meter) { 
    return Vect2D(static_cast<int>((meter.x-0.12f) * 100.0f), static_cast<int>(5000.00f - ((0.245+meter.y) * 100.0f)));
}

BoxManager::BoxManager(): worms(), world(worms) {
    set_map();
    std::cout << "BoxManager created con " << std::to_string(worms.size()) << " gusanos" << std::endl;
    playing_worm = worms.begin();
}

void BoxManager::add_player() {
    float x = 0.5f;
    float y = 49.5f;
    world.create_worm(x, y, worms.size());
    if(worms.size() == 1)
        playing_worm = worms.begin();
}

void BoxManager::next_turn(int player_id) {
    std::cout << "Next turn en b2d manager y va al " << std::to_string(player_id) << std::endl;
    // // if(++playing_worm == worms.end())
    // //     playing_worm = worms.begin();
    // if (playing_worm == worms.end()) {
    //     playing_worm = worms.begin();
    //     return;
    // }
    // ++playing_worm;
    // if (playing_worm == worms.end()) {
    //     playing_worm = worms.begin();
    // }
    auto it = worms.begin();
    std::advance(it, player_id - 1);
    playing_worm = it;
}

// should later introduce to recive the map position automatically
bool BoxManager::set_map() {
    CommonMapParser parser;
    return world.set_map(parser.get_map("mapita.yaml"));
}

std::map<int, Vect2D>* BoxManager::create_position_map(const std::list<Box2DPlayer>& worms) {
    std::map<int, Vect2D>* positions = new std::map<int, Vect2D>();
    int i = 1;
    for (auto worm : worms) {
        b2Body* body = worm.get_body(); // Obtener el cuerpo
        if (body) { // Verificar si el cuerpo es válido
            b2Vec2 pos = body->GetPosition();
            positions->insert(std::make_pair(i, meter_to_pixel(pos)));
            i++;
        }
    }
    return positions;
}

std::shared_ptr<WorldUpdate> BoxManager::process(std::shared_ptr<Box2DMsg> update) {
    b2Body* current = (*playing_worm).get_body();
    int current_command = update->get_cmd();        
    b2Vec2 vel = current->GetLinearVelocity();  // vector vel del gusano
    b2ContactEdge* contacts = current->GetContactList();

    switch (current_command) {
        case COMMAND_LEFT:
            vel.x = -1.0f;  // modifico componente en x
            direction = LEFT;
            break;
        case COMMAND_RIGHT:
            vel.x = 1.0f;
            direction = RIGHT;
            break;
        case COMMAND_STOP:
            vel.x = 0.0f;
            break;
        case COMMAND_JUMP_FOWARD:
            if (contacts != nullptr && contacts->contact != nullptr) {
                current->ApplyLinearImpulse(b2Vec2(0.1f, 0.45f), current->GetWorldCenter(), true);
            }
            break;
        
        case COMMAND_JUMP_BACKWARD:
            if (contacts != nullptr && contacts->contact != nullptr) {
                current->ApplyLinearImpulse(b2Vec2(0.1f, 0.45f), current->GetWorldCenter(), true);
            }
            break; 

        case COMMAND_NEXT:
            this->next_turn(update->get_id());
            break;
        
        // case COMMAND_FIRE:
            // this->player_shoot(update->get_angle(), update->get_power(), update->get_type());
            // break; 
        
        // case COMMAND_SPECIAL_SHOOT:
        //     this->player_special_shoot(update->get_position(), update->get_type());
        //     break;

        default:
            vel.x = 0.0f;
            break;
    }
    current->SetLinearVelocity(vel);  // seteo la nueva velocidad
    world.step();
    return std::make_shared<WorldUpdate>(create_position_map(worms)); // TODO: ver que devolver
}

/*  
  Power should be a float that goes from 0 to 1 to represent the proportion of power induced
  by the player to the shot. Angle represents the angle in degrees relative to the floor the 
  player aims.
*/
void BoxManager::fire_projectile(float angle, float power, float restitution, int category, int mask) {
    b2Body* projectile = world.create_projectile(playing_worm->get_body()->GetPosition().x, playing_worm->get_body()->GetPosition().y, restitution, this->direction, category, mask);
    b2Vec2 Vector = b2Vec2( (power*0.001f)*cos(angle*DEGTORAD), (power*0.001f)*sin(angle*DEGTORAD) );
    if(direction == LEFT)
        Vector.x = -Vector.x;
    projectile->ApplyLinearImpulseToCenter( Vector , true );
    projectile->SetBullet(true);
    projectiles.push_back(projectile);  
}

void BoxManager::player_shoot(float angle, float power, int type) {
    switch(type){
        case BAZOOKA:
            Bazooka(this).fire(angle, power);
            break;
        case MORTAR:
            Mortar(this).fire(angle, power);
            break;
        case GREEN_GRANADE:
            GreenGranade(this).fire(angle, power);
            break;
        case RED_GRANADE:
            RedGranade(this).fire(angle, power);
            break;
        case BANANA:
            Banana(this).fire(angle, power);
            break;
        case HOLY_GRANADE:
            HolyGranade(this).fire(angle, power);
            break;
        case DYNAMITE:
            // Dynamite(this).fire(angle, power);
            break;
        case BASEBALL_BAT:
            // BaseballBat(this).fire(angle, power);
            break;
        
    }
}


// BoxManager::player_special_shoot(update.get_position(), update.get_type()) {
//     switch(type){
//         case AIR_STRIKE:
//             AirAttack(this).fire(angle, power);
//             break;
//         case TELEPORT:
//             Teleport(this).fire(angle, power);
//             break;
//     }
// }