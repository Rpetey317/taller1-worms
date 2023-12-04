#include "box2dManager.h"
#include "Vect2D.h"
#include <iostream>
#include "../Box2DWeapons/WeaponsHeaders.h"
#include "../../../src/Message/Box2DMsg/Box2DMsgHeaders.h"

#define DEGTORAD -0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define LEFT 1
#define RIGHT 0

Vect2D BoxManager::meter_to_pixel(b2Vec2 meter) { 
    return Vect2D(static_cast<int>((meter.x-0.12f) * 100.0f), static_cast<int>(5000.00f - ((0.245+meter.y) * 100.0f)));
}

BoxManager::BoxManager(): worms(), world(worms), timer_allows(true) {
    set_map();
    std::cout << "BoxManager created con " << std::to_string(worms.size()) << " gusanos" << std::endl;
    playing_worm = worms.begin();
}

void BoxManager::next_turn(int player_id) {
    std::cout << "Next turn en b2d manager y va al " << std::to_string(player_id) << std::endl;
    auto it = worms.begin();
    std::advance(it, player_id - 1);
    playing_worm = it;
}

// should later introduce to recive the map position automatically
bool BoxManager::set_map() {
    CommonMapParser parser;
    return world.set_map(parser.get_map("mapita.yaml"));
}

std::map<int, Worm>* BoxManager::create_position_map(const std::list<Box2DPlayer>& worms) {
    std::map<int, Worm>* worms_position = new std::map<int, Worm>();
    for (auto worm : worms) {
        b2Body* body = worm.get_body(); // Obtener el cuerpo
        if (body && worm.is_alive()) { // Verificar si el cuerpo es válido
            b2Vec2 pos = body->GetPosition();
            Worm worm_class( meter_to_pixel(pos), worm.get_id(), worm.get_state(), worm.get_health_points());
            worms_position->insert(std::make_pair(worm.get_id(), worm_class));
        }
    }
    return worms_position;
}


std::map<int, WeaponDTO>* BoxManager::create_proyectile_map(const std::list<b2Body*>& projectiles) {
    std::map<int, WeaponDTO>* positions = new std::map<int, WeaponDTO>();
    int i = 1;
    for (auto projectile : projectiles) {
        if (projectile) { // Verificar si el cuerpo es válido
            b2Vec2 pos = projectile->GetPosition();
            int angle = (int)acos(projectile->GetLinearVelocity().x / projectile->GetLinearVelocity().Length()) * RADTODEG;
            Box2DPlayer* temp = (Box2DPlayer*)(projectile->GetUserData().pointer);
            WeaponDTO weapon(temp->get_id(), meter_to_pixel(pos), angle);
            positions->insert(std::make_pair(i, weapon));
        }
        i++;
    }
    return positions;
}

std::shared_ptr<WorldUpdate> BoxManager::process(std::shared_ptr<Box2DMsg> update) {
    b2Body* current = (*playing_worm).get_body();
    int current_command = update->get_cmd();        
    b2Vec2 vel = current->GetLinearVelocity();  // vector vel del gusano
    b2ContactEdge* contacts = current->GetContactList();

    Box2DPlayer* temp = (Box2DPlayer*)(current->GetUserData().pointer);
    switch (current_command) {
        case COMMAND_LEFT:
            vel.x = -1.0f;  // modifico componente en x
            if (temp) {
                temp->set_direction(LEFT);
            }
            break;
        case COMMAND_RIGHT:
            vel.x = 1.0f;
            if (temp) {
                temp->set_direction(RIGHT);
            }
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
            this->world.clean_projectiles(true);
            break;
        
        case COMMAND_SHOOT:
            // this->player_shoot(update->get_angle(), update->get_power(), update->get_weapon_id());
            break; 
        
        case COMMAND_SPECIAL_SHOOT:
            // this->player_special_shoot(update->get_position(), update->get_weapon_id());
            break;
        
        // case COMMAND_TIMER:
        //     this->world.timer_allows = true;
        //     break;

        default:
            vel.x = 0.0f;
            break;
    }
    current->SetLinearVelocity(vel);  // seteo la nueva velocidad
    world.step();
    // this->create_proyectile_map(this->world.projectiles);
    return std::make_shared<WorldUpdate>(create_position_map(worms), create_proyectile_map(this->world.projectiles)); // TODO: ver que devolver
}

/*  
  Power should be a float that goes from 0 to 1 to represent the proportion of power induced
  by the player to the shot. Angle represents the angle in degrees relative to the floor the 
  player aims.
*/
void BoxManager::fire_projectile(float angle, float power, float restitution, int category, int mask, bool set_timer, int type) {
    Box2DPlayer* temp = (Box2DPlayer*)(playing_worm->get_body()->GetUserData().pointer);
    b2Body* projectile = world.create_projectile(playing_worm->get_body()->GetPosition().x, playing_worm->get_body()->GetPosition().y, restitution, temp->get_direction(), category, mask, set_timer, type);
    b2Vec2 Vector = b2Vec2( (power*0.001f)*cosf(angle*DEGTORAD), (power*0.001f)*sinf(angle*DEGTORAD) );
    if(temp->get_direction() == LEFT)
        Vector.x = -Vector.x;
    projectile->SetBullet(true);
    projectile->ApplyLinearImpulseToCenter( Vector , true );
}

void BoxManager::player_shoot(int angle, int power, int weapon_type) {
    float fangle = static_cast<float>(angle);
    float fpower = static_cast<float>(power);
    switch(weapon_type){
        case BAZOOKA:
            Bazooka(this).fire(fangle, fpower);
            break;
        case MORTAR:
            Mortar(this).fire(fangle, fpower);
            break;
        case GREEN_GRANADE:
            GreenGranade(this).fire(fangle, fpower);
            break;
        case RED_GRANADE:
            RedGranade(this).fire(fangle, fpower);
            break;
        case BANANA:
            Banana(this).fire(fangle, fpower);
            break;
        case HOLY_GRANADE:
            HolyGranade(this).fire(fangle, fpower);
            break;
        case DYNAMITE:
            Dynamite(this).fire(fangle, fpower);
            break;
        case BASEBALL_BAT:
            // BaseballBat(this).fire(fangle, fpower);
            break;
        
    }
}

void BoxManager::air_strike(Vect2D position) {
    world.air_strike(position);
}

void BoxManager::teleport(Vect2D position) {
    world.teleport(position, playing_worm->get_body());
}

void BoxManager::dynamite(float restitution, int category, int mask) {
    Box2DPlayer* temp = (Box2DPlayer*)(playing_worm->get_body()->GetUserData().pointer);
    world.create_projectile(playing_worm->get_body()->GetPosition().x, playing_worm->get_body()->GetPosition().y, restitution, temp->get_direction(), category, mask, false, DYNAMITE);
}

void BoxManager::baseball_bat(float angle, float power) {
    Box2DPlayer* temp = (Box2DPlayer*)(playing_worm->get_body()->GetUserData().pointer);
    world.baseball_bat(playing_worm->get_body(), angle, power, temp->get_direction());
}

void BoxManager::player_special_shoot(Vect2D position, int weapon_type) {
    switch(weapon_type){
        case AIR_STRIKE:
            AirAttack(this).fire_special(position);
            break;
        case TELEPORT:
            Teleport(this).fire_special(position);
            break;
    }
}

