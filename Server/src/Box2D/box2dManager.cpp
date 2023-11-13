#include "box2dManager.h"

#define COMMAND_STOP 0
#define COMMAND_EXIT -1
#define COMMAND_RIGHT 1
#define COMMAND_LEFT 2
#define COMMAND_JUMP 3


void BoxSimulator::initialize_world() {
    // creo el mundo
    b2Vec2 gravity(0.0f, -9.8f);  // se le da el valor de gravedad que querramos
    world = new b2World(gravity);

    // GUSANO
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;       // es dinamico (aplican fuerzas)
    myBodyDef.position.Set(0.20f, 0.20f);  // pos inicial
    myBodyDef.angle = 0;                   // angulo inicial
    worm = world->CreateBody(&myBodyDef);  // añado el cuerpo al mundo

    b2PolygonShape boxShape;          // creo una forma
    boxShape.SetAsBox(0.12f, 0.15f);  // forma del gusano 24x30
    b2FixtureDef boxFixtureDef;       // creo un fixture
    boxFixtureDef.shape = &boxShape;  // le doy la forma de la forma creada
    boxFixtureDef.density = 1;
    worm->CreateFixture(&boxFixtureDef);  // añado el fixture
    worm->SetFixedRotation(true);         // le saco la rotacion al cuerpo
    // PLATAFORMA
    boxShape.SetAsBox(0.64f, 0.095f);  // forma de caja 128x19
    boxFixtureDef.shape = &boxShape;   // le doy la forma de la forma creada

    // puedo re usar la definicion
    myBodyDef.type = b2_staticBody;                      // estatico
    myBodyDef.position.Set(3.84f, 1.425f);               // posicion
    b2Body* staticBody = world->CreateBody(&myBodyDef);  // add body to world
    staticBody->CreateFixture(&boxFixtureDef);           // add fixture to body

    // PAREDES
    b2EdgeShape edgeShape;
    // fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &edgeShape;
    myFixtureDef.density = 1;

    // a static floor to drop things on
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0.0f, 0.0f);
    edgeShape.SetTwoSided(b2Vec2(0.0f, 0.0f), b2Vec2(6.4f, 0.0f));
    world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

    // a static wall right
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0.0f, 0.0f);
    edgeShape.SetTwoSided(b2Vec2(0.0f, 0.0f), b2Vec2(0.0f, 1.9f));
    world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

    // a static wall left
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0.0f, 0.0f);
    edgeShape.SetTwoSided(b2Vec2(6.4f, 0.0f), b2Vec2(6.4f, 1.9f));
    world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

    // a static roof
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0.0f, 0.0f);
    edgeShape.SetTwoSided(b2Vec2(0.0f, 1.9f), b2Vec2(6.4f, 1.9f));
    world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
}


BoxSimulator::BoxSimulator(Queue<int>& commands, Queue<std::vector<int>>& positions):
        ingoing(commands), outgoing(positions) {
    initialize_world();
}


void BoxSimulator::run() {
    float timeStep = 1.0f / 60.0f; // Paso de tiempo para la simulación (60 FPS)
    int32 velocityIterations = 6; 
    int32 positionIterations = 2;

    int current_command = COMMAND_STOP;
    while (current_command != COMMAND_EXIT) {
        current_command = ingoing.pop();
        b2Vec2 vel = worm->GetLinearVelocity();  // vector vel del gusano
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
                if (worm->GetLinearVelocity().y == 0) {
                    worm->ApplyLinearImpulse(b2Vec2(0.0f, 1.0f), worm->GetWorldCenter(), true);
                }
                break;
            default:
                vel.x = 0.0f;
                break;
        }
        worm->SetLinearVelocity(vel);  // seteo la nueva velocidad
        world->Step(timeStep, velocityIterations, positionIterations); //simulo un paso con la info actual
        b2Vec2 pos = worm->GetPosition(); //consigo la pos
        std::vector<int> positions = {int(pos.x*100.0f), int(pos.y*100.0f)};
        outgoing.push(positions); //paso la pos
    }
}

void BoxSimulator::kill() {
    delete world;
}
