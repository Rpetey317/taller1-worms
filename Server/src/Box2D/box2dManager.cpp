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

b2Body* BoxSimulator::create_worm(float x, float y) {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; 
    myBodyDef.position.Set(x, y); 
    myBodyDef.angle = 0; 
    b2Body *worm = world->CreateBody(&myBodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(0.12f,0.15f); 
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.friction = 0.2f;
    worm->CreateFixture(&boxFixtureDef);
    worm->SetFixedRotation(true);

    return worm;
}

void BoxSimulator::create_wall(b2Vec2 start, b2Vec2 end){
    b2EdgeShape edgeShape;
    //fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &edgeShape;
    myFixtureDef.density = 1;
    myFixtureDef.friction = 0.4f;
    //a static floor to drop things on
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0.0f, 0.0f);
    edgeShape.SetTwoSided(start, end);
    world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
}

void BoxSimulator::create_ground(b2Vec2 lower_l, b2Vec2 lower_r, b2Vec2 upper_l, b2Vec2 upper_r){
    // creo el mundo
    b2PolygonShape boxShape;
    b2BodyDef myBodyDef;

    // Crear muros y piso
    create_wall(lower_l, lower_r);
    create_wall(upper_l, upper_r);
    create_wall(lower_l, upper_l);
    create_wall(lower_r, upper_r);
}

void BoxSimulator::create_long_beam(b2Vec2 start, float angle){
    b2PolygonShape beamShape;
    b2FixtureDef beamFixtureDef;
    b2BodyDef myBodyDef;

    beamShape.SetAsBox(0.64f,0.095f); // forma de caja de 2x2
    beamFixtureDef.shape = &beamShape; // le doy la forma de la forma creada
    if(angle < 45.0f)
        beamFixtureDef.friction = 2.5f;

    myBodyDef.type = b2_staticBody; //this will be a static body
    myBodyDef.position.Set(start.x + 0.64f, start.y - 0.095f); //slightly lower position
    myBodyDef.angle = angle; //set the starting angle
    b2Body* staticBody = world->CreateBody(&myBodyDef); //add body to world
    staticBody->CreateFixture(&beamFixtureDef); //add fixture to body
}

void BoxSimulator::create_short_beam(b2Vec2 start, float angle){
    b2PolygonShape beamShape;
    b2FixtureDef beamFixtureDef;
    b2BodyDef myBodyDef;

    beamShape.SetAsBox(0.32f,0.095f); // forma de caja de 2x2
    beamFixtureDef.shape = &beamShape; // le doy la forma de la forma creada
    if(angle < 45.0f)
        beamFixtureDef.friction = 2.5f;

    myBodyDef.type = b2_staticBody; //this will be a static body
    myBodyDef.position.Set(start.x + 0.64f, start.y - 0.095f); //slightly lower position
    myBodyDef.angle = angle; //set the starting angle
    b2Body* staticBody = world->CreateBody(&myBodyDef); //add body to world
    staticBody->CreateFixture(&beamFixtureDef); //add fixture to body
}

void create_map(){
    // create_long_beam();
    // create_short_beam();	
}

void BoxSimulator::add_player() {
    float x = 0.0f;
    float y = 0.0f;
    worms.push_back(Box2DPlayer(worms.size(), create_worm(x, y)));
    if(worms.size() == 1)
        playing_worm = worms.begin();
}

void BoxSimulator::next_turn() {
    if(++playing_worm == worms.end())
        playing_worm = worms.begin();
}

void BoxSimulator::initialize_world() {
    // creo el mundo
    b2Vec2 gravity(0.0f, -9.8f);  // se le da el valor de gravedad que querramos
    world = new b2World(gravity);
    float height = 4.0f;
    float width = 10.0f;
    create_ground(b2Vec2(0.0f,0.0f), b2Vec2(width,0.0f), b2Vec2(0.0f,height), b2Vec2(width, height)); 
    add_player();
    create_map(); 
}

BoxSimulator::BoxSimulator(Queue<int>& commands, Queue<std::vector<int>>& positions):
        ingoing(commands), outgoing(positions) {
    initialize_world();
}

std::map<int, Vect2D>* create_position_map(const std::list<Box2DPlayer>& worms) {
    std::map<int, Vect2D>* positions = new std::map<int, Vect2D>();
    for (auto worm : worms) {
        b2Body* body = worm.get_body(); // Obtener el cuerpo
        if (body) { // Verificar si el cuerpo es válido
            b2Vec2 pos = body->GetPosition();
            Vect2D position(static_cast<int>(pos.x * 100.0f), static_cast<int>(pos.y * 100.0f));
            positions->insert(std::make_pair(worm.get_id(), position));
        }
    }
    return positions;
}


GameWorldUpdate* BoxSimulator::process(ClientBox2DUpdate& update) {

    float timeStep = 1.0f / 60.0f;  // Paso de tiempo para la simulación (60 FPS)
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
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
    world->Step(timeStep, velocityIterations, positionIterations); // esto no deberia depender de los updates, deberia correr en un hilo. (puede ser llamado por el hilo server(?))
    return new GameWorldUpdate(create_position_map(worms)); // TODO: ver que devolver
}

void BoxSimulator::kill() { delete world; }
