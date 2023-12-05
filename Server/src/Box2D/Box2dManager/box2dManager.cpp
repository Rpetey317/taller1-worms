#include "box2dManager.h"
#include "Vect2D.h"
#include <iostream>
#include "../Box2DWeapons/WeaponsHeaders.h"
#include "../../../src/Message/Box2DMsg/Box2DMsgHeaders.h"
#include <yaml-cpp/yaml.h> // Add this line to include the yaml-cpp header

#define LEFT 1
#define RIGHT 0

Vect2D BoxManager::meter_to_pixel(b2Vec2 meter, float offset_x, float offset_y) { 
    // return Vect2D(static_cast<int>((meter.x-0.12f) * configurator.get_box2D_configuration().meters_to_pixel), static_cast<int>(5000.00f - ((0.245+meter.y) * configurator.get_box2D_configuration().meters_to_pixel)));
    return Vect2D(static_cast<int>((meter.x-offset_x) * configurator.get_box2D_configuration().meters_to_pixel), static_cast<int>(5000.00f - ((offset_y+meter.y) * configurator.get_box2D_configuration().meters_to_pixel)));
}

BoxManager::BoxManager(std::string file_name): worms(), world(worms), timer_allows(true) {
    set_map(file_name);
    std::cout << "BoxManager created con " << std::to_string(worms.size()) << " gusanos" << std::endl;
    playing_worm = worms.begin();
}


void BoxManager::next_turn(int worm_id) {
    std::cout << "Next turn en b2d manager y va al " << std::to_string(worm_id) << std::endl;
    auto it = worms.begin();
    std::advance(it, worm_id - 1);
    playing_worm = it;
}

// should later introduce to recive the map position automatically
bool BoxManager::set_map(std::string file_name) {
    CommonMapParser parser;
    map_name = file_name;
    std::cout << "creando mapita" << std::endl;
    return world.set_map(parser.get_map(file_name));
}

std::map<int, Worm>* BoxManager::create_position_map(const std::list<Box2DPlayer>& worms) {
    std::cout << "creando mapa de posiciones en Box2dManager (39)" << std::endl;
    std::map<int, Worm>* worms_position = new std::map<int, Worm>();
    for (auto worm : worms) {
        b2Body* body = worm.get_body(); // Obtener el cuerpo
        if (body) { // Verificar si el cuerpo es válido
            b2Vec2 pos = body->GetPosition();
            if(worm.is_falling() && worm.get_state() != WORM_DEAD)
                worm.set_state(WORM_FALLING);
            std::cout << "posicion del gusano segun b2d " << std::to_string(worm.get_id()) << " es " << std::to_string(meter_to_pixel(pos, 0.12f, 0.245f).x) << " " << std::to_string(meter_to_pixel(pos, 0.12f, 0.245f).y) << std::endl;
            
            Worm worm_class( meter_to_pixel(pos, 0.12f, 0.245f), worm.get_state(), worm.get_id(), worm.get_team_id(), worm.get_health_points(), map_name);
            worms_position->insert(std::make_pair(worm.get_id(), worm_class));
            
        }
    }
    return worms_position;
}


std::map<int, WeaponDTO>* BoxManager::create_proyectile_map(const std::list<b2Body*>& projectiles) {
    std::map<int, WeaponDTO>* positions = new std::map<int, WeaponDTO>();
    int i = 1;
    std::cout << "creando mapa de proyectiles en Box2dManager (57)" << std::endl;
    for (auto projectile : projectiles) {
        if (projectile) { // Verificar si el cuerpo es válido
            b2Vec2 pos = projectile->GetPosition();
            int angle = (int)acos(projectile->GetLinearVelocity().x / projectile->GetLinearVelocity().Length()) * configurator.get_box2D_configuration().rad_to_deg;
            Box2DPlayer* temp = (Box2DPlayer*)(projectile->GetUserData().pointer);
            std::cout << "posicion del proyectil segun b2d " << std::to_string(temp->get_id()) << " es " << std::to_string(meter_to_pixel(pos, 0.12f, 0.245f).x) << " " << std::to_string(meter_to_pixel(pos, 0.12f, 0.245f).y) << "en angulo " << std::to_string(angle) << std::endl;
            WeaponDTO weapon(temp->get_id(), meter_to_pixel(pos, 0.12f, 0.245f), angle);
            positions->insert(std::make_pair(i, weapon));
        }
        i++;
    }
    return positions;
}

void BoxManager::tick() {
    this->time_ticker++;
}

void BoxManager::set_teams(int worm_id, int player_id) {
    this->world.set_teams(worm_id, player_id);
}

std::shared_ptr<WorldUpdate> BoxManager::process(std::shared_ptr<Box2DMsg> update) {
    b2Body* current = (*playing_worm).get_body();
    int current_command = update->get_cmd();        
    b2Vec2 vel = current->GetLinearVelocity();  // vector vel del gusano
    b2ContactEdge* contacts = current->GetContactList();

    Box2DPlayer* temp = (Box2DPlayer*)(current->GetUserData().pointer);
    std::shared_ptr<BoxShoot> sh_update;
    std::shared_ptr<BoxSpecialShoot> spsh_update;
    switch (current_command) {
        case COMMAND_LEFT:
            vel.x = -configurator.get_worm_configuration().speed;  // modifico componente en x
            if (temp) {
                temp->set_direction(LEFT);
                temp->set_state(WORM_WALKING);
            }
            break;
        case COMMAND_RIGHT:
            vel.x = configurator.get_worm_configuration().speed;
            if (temp) {
                temp->set_direction(RIGHT);
                temp->set_state(WORM_WALKING);
            }
            break;
        case COMMAND_STOP:
            vel.x = 0.0f;
            if (temp) {
                temp->set_state(WORM_STILL);
            }
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
            this->time_ticker = 0;
            break;
        case COMMAND_SHOOT:
            sh_update = std::static_pointer_cast<BoxShoot>(update);
            this->player_shoot(sh_update->get_angle(), sh_update->get_power(), sh_update->get_weapon_id());
            break; 
        case COMMAND_SPECIAL_SHOOT:
            spsh_update = std::static_pointer_cast<BoxSpecialShoot>(update);
            this->player_special_shoot(spsh_update->get_position(), spsh_update->get_weapon_id());
            break;
        case COMMAND_NULL:
            break;
        default:
            vel.x = 0.0f;
            if(temp){
                temp->set_state(WORM_STILL);
            }
            break;
    }
    if((this->time_ticker - this->detonation_tick) > 75){
        this->world.timer_allows = true;
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
void BoxManager::fire_projectile(float angle, float power, float restitution, int category, int mask, bool has_to_wait, int type, bool wind_affects) {
    Box2DPlayer* temp = (Box2DPlayer*)(playing_worm->get_body()->GetUserData().pointer);
    b2Body* projectile = world.create_projectile(playing_worm->get_body()->GetPosition().x, playing_worm->get_body()->GetPosition().y, restitution, temp->get_direction(), category, mask, has_to_wait, type);
    b2Vec2 Vector = b2Vec2( (power*0.001f)*cosf(angle*configurator.get_box2D_configuration().deg_to_rad), (power*0.001f)*sinf(angle*configurator.get_box2D_configuration().deg_to_rad) );
    if(temp->get_direction() == LEFT)
        Vector.x = -Vector.x;
    // if(this->wind != 0.0f && wind_affects)
    //     Vector.x += this->wind;
    projectile->SetBullet(true);
    projectile->ApplyLinearImpulseToCenter( Vector , true );
}

void BoxManager::player_shoot(int angle, int power, int weapon_type) {
    float fangle = static_cast<float>(angle);
    float fpower = static_cast<float>(power);
    WeaponConfiguration config;
    switch(weapon_type){
        case BAZOOKA:
            config = configurator.get_weapons_configuration().bazooka;
            Bazooka(this).fire(fangle, fpower, config.restitution, config.timer , config.wind);
            break;
        case MORTAR:
            config = configurator.get_weapons_configuration().mortar;
            Mortar(this).fire(fangle, fpower, config.restitution, config.timer , config.wind);
            break;
        case GREEN_GRANADE:
            config = configurator.get_weapons_configuration().green_grenade;
            this->detonation_tick = this->time_ticker;
            GreenGranade(this).fire(fangle, fpower, config.restitution, config.timer , config.wind);
            break;
        case RED_GRANADE:
            config = configurator.get_weapons_configuration().red_grenade;
            this->detonation_tick = this->time_ticker;
            RedGranade(this).fire(fangle, fpower, config.restitution, config.timer , config.wind);
            break;
        case BANANA:
            config = configurator.get_weapons_configuration().banana;
            this->detonation_tick = this->time_ticker;
            Banana(this).fire(fangle, fpower, config.restitution, config.timer , config.wind);
            break;
        case HOLY_GRANADE:
            config = configurator.get_weapons_configuration().holy_grenade;
            this->detonation_tick = this->time_ticker;
            HolyGranade(this).fire(fangle, fpower, config.restitution, config.timer , config.wind);
            break;
        case DYNAMITE:
            config = configurator.get_weapons_configuration().dynamite;
            this->detonation_tick = this->time_ticker;
            Dynamite(this).fire(fangle, fpower, config.restitution, config.timer , config.wind);
            break;
        case BASEBALL_BAT:
            config = configurator.get_weapons_configuration().baseball;
            BaseballBat(this).fire(fangle, fpower, config.restitution, config.timer , config.wind);
            break;
        
    }
}

void BoxManager::air_strike(Vect2D position) {
    world.air_strike(position);
}

void BoxManager::teleport(Vect2D position) {
    world.teleport(position, playing_worm->get_body());
}

void BoxManager::dynamite(float restitution, int category, int mask, bool has_to_wait) {
    Box2DPlayer* temp = (Box2DPlayer*)(playing_worm->get_body()->GetUserData().pointer);
    world.create_projectile(playing_worm->get_body()->GetPosition().x, playing_worm->get_body()->GetPosition().y, restitution, temp->get_direction(), category, mask, has_to_wait, DYNAMITE);
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

