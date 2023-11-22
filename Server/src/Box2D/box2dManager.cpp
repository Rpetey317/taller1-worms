#include "box2dManager.h"
#include "Vect2D.h"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define COMMAND_STOP 0
#define COMMAND_EXIT -1
#define COMMAND_RIGHT 1
#define COMMAND_LEFT 2
#define COMMAND_JUMP 3
#define COMMAND_NEXT 4

BoxSimulator::BoxSimulator(): world() {}

void BoxSimulator::add_player() {
    float x = 0.0f;
    float y = 0.0f;
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
    return world.set_map(parser.get_map("../../../maps/mapita.txt"));
}

std::map<int, Vect2D>* create_position_map(const std::list<Box2DPlayer>& worms) {
    std::map<int, Vect2D>* positions = new std::map<int, Vect2D>();
    for (auto worm : worms) {
        b2Body* body = worm.get_body(); // Obtener el cuerpo
        if (body) { // Verificar si el cuerpo es válido
            b2Vec2 pos = body->GetPosition();
            Point position(static_cast<int>((pos.x * 100.0f)-WORM_HALF_WIDTH), static_cast<int>((pos.y * 100.0f)+WORM_HALF_HEIGHT));
            positions->insert(std::make_pair(worm.get_id(), position));
        }
    }
    return positions;
}

GameWorldUpdate* BoxSimulator::process(ClientBox2DUpdate& update) {
    int current_command = update.get_cmd();        
    b2Vec2 vel = (*playing_worm).get_body()->GetLinearVelocity();  // vector vel del gusano
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
            if ((*playing_worm).get_body()->GetLinearVelocity().y == 0) {
                (*playing_worm).get_body()->ApplyLinearImpulse(b2Vec2(0.1f, 0.45f), (*playing_worm).get_body()->GetWorldCenter(), true);
            }
            break;
        case COMMAND_NEXT:
            this->next_turn();
            break;
        default:
            vel.x = 0.0f;
            break;
    }
    (*playing_worm).get_body()->SetLinearVelocity(vel);  // seteo la nueva velocidad
    world.step();
    return new GameWorldUpdate(create_position_map(worms)); // TODO: ver que devolver
}

void BoxSimulator::player_shoot(float angle, float power) {
    // To implement
}
