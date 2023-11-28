#include "box2dManager.h"
#include "Vect2D.h"

#define DEGTORAD -0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define COMMAND_STOP 0
#define COMMAND_EXIT -1
#define COMMAND_RIGHT 1
#define COMMAND_LEFT 2
#define COMMAND_JUMP 3
#define COMMAND_NEXT 4

Vect2D BoxSimulator::meter_to_pixel(b2Vec2 meter) { 
    return Vect2D(static_cast<int>((meter.x-0.12f) * 100.0f), static_cast<int>(5000.00f - ((0.245+meter.y) * 100.0f)));
}


BoxSimulator::BoxSimulator(): world() {
    set_map();
}

void BoxSimulator::add_player() {
    float x = 0.5f;
    float y = 49.5f;
    worms.push_back(Box2DPlayer(worms.size(), world.create_worm(x, y)));
    if(worms.size() == 1)
        playing_worm = worms.begin();
}

void BoxSimulator::next_turn() {
    if(++playing_worm == worms.end())
        playing_worm = worms.begin();
}

// should later introduce to recive the map position automatically
bool BoxSimulator::set_map() {
    CommonMapParser parser;
    return world.set_map(parser.get_map("../maps/mapita.txt"));
}
#include <iostream>
std::map<int, Vect2D>* BoxSimulator::create_position_map(const std::list<Box2DPlayer>& worms) {
    std::map<int, Vect2D>* positions = new std::map<int, Vect2D>();
    for (auto worm : worms) {
        b2Body* body = worm.get_body(); // Obtener el cuerpo
        if (body) { // Verificar si el cuerpo es válido
            b2Vec2 pos = body->GetPosition();
            positions->insert(std::make_pair(worm.get_id(), meter_to_pixel(pos)));
        }
    }
    return positions;
}

std::shared_ptr<GameWorldUpdate> BoxSimulator::process(Box2DMsg& update) {
    b2Body* current = (*playing_worm).get_body();
    int current_command = update.get_cmd();        
    b2Vec2 vel = current->GetLinearVelocity();  // vector vel del gusano
    b2ContactEdge* contacts = current->GetContactList();

    switch (current_command) {
        case COMMAND_LEFT:
            vel.x = -1.0f;  // modifico componente en x
            break;
        case COMMAND_RIGHT:
            vel.x = 1.0f;
            break;
        case COMMAND_STOP:
            vel.x = 0.0f;
            break;
        case COMMAND_JUMP:
            if (contacts != nullptr && contacts->contact != nullptr) {
                current->ApplyLinearImpulse(b2Vec2(0.1f, 0.45f), current->GetWorldCenter(), true);
            }
            break;
        case COMMAND_NEXT:
            this->next_turn();
            break;
        default:
            vel.x = 0.0f;
            break;
    }
    current->SetLinearVelocity(vel);  // seteo la nueva velocidad
    world.step();
    return std::make_shared<GameWorldUpdate>(create_position_map(worms)); // TODO: ver que devolver
}

void BoxSimulator::player_shoot(float angle, float power) {
    // To implement
}
