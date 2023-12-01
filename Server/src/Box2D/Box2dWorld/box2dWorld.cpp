#include "box2dWorld.h"

#define DEGTORAD -0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define SHORT_BEAM '0'
#define LONG_BEAM '1'

enum _entityCategory {
    BEAM = 0x0001,
    WORM = 0x0002,
};

BoxWorld::BoxWorld() {
    initialize_world();
}

void BoxWorld::initialize_world() {
    // creo el mundo
    b2Vec2 gravity(0.0f, -9.8f);  // se le da el valor de gravedad que querramos
    world = new b2World(gravity);
    float height = 50.0f;
    float width = 200.0f;
    float zero = -0.15f;
    create_ground(b2Vec2(zero,zero), b2Vec2(width,zero), b2Vec2(zero,height), b2Vec2(width, height)); 
    //set_map
}

b2Body* BoxWorld::create_worm(float x, float y) {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; 
    myBodyDef.position.Set(x, y); 
    myBodyDef.angle = 0; 
    b2Body *worm = world->CreateBody(&myBodyDef);

    b2Vec2 vertices[6];
    vertices[0].Set(-0.06f, -0.15f);
    vertices[1].Set(-0.12f, -0.1f);
    vertices[2].Set(-0.12f, 0.15);
    vertices[3].Set( 0.12f, 0.15f);
    vertices[4].Set( 0.12f, -0.1f);
    vertices[5].Set( 0.06f, -0.15f);
    b2PolygonShape wormShape;
    wormShape.Set(vertices, 6);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &wormShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.friction = 0.2f;
    boxFixtureDef.filter.categoryBits = WORM;
    boxFixtureDef.filter.maskBits = BEAM;
    worm->CreateFixture(&boxFixtureDef);
    worm->SetFixedRotation(true);

    return worm;
}

void BoxWorld::create_wall(b2Vec2 start, b2Vec2 end){
    b2EdgeShape edgeShape;
    b2FixtureDef myFixtureDef;

    myFixtureDef.shape = &edgeShape;
    myFixtureDef.density = 1;
    myFixtureDef.friction = 0.4f;

    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0.0f, 0.0f);
    edgeShape.SetTwoSided(start, end);
    world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
}

void BoxWorld::create_ground(b2Vec2 lower_l, b2Vec2 lower_r, b2Vec2 upper_l, b2Vec2 upper_r){
    // creo el mundo
    b2PolygonShape boxShape;
    b2BodyDef myBodyDef;

    // Crear muros y piso
    create_wall(lower_l, lower_r);
    create_wall(upper_l, upper_r);
    create_wall(lower_l, upper_l);
    create_wall(lower_r, upper_r);
}

void BoxWorld::create_long_beam(b2Vec2 start, float angle){
    b2PolygonShape beamShape;
    b2FixtureDef beamFixtureDef;
    b2BodyDef myBodyDef;

    beamShape.SetAsBox(0.64f,0.095f); // forma de caja de 2x2
    beamFixtureDef.shape = &beamShape; // le doy la forma de la forma creada
    beamFixtureDef.filter.categoryBits = BEAM;
    beamFixtureDef.filter.maskBits = WORM;
    if(angle < 45.0f)
        beamFixtureDef.friction = 2.5f;

    myBodyDef.type = b2_staticBody; //this will be a static body
    myBodyDef.position.Set(start.x + 0.64f, start.y - 0.095f); //slightly lower position
    myBodyDef.angle = angle * DEGTORAD; //set the starting angle
    b2Body* staticBody = world->CreateBody(&myBodyDef); //add body to world
    staticBody->CreateFixture(&beamFixtureDef); //add fixture to body
}

void BoxWorld::create_short_beam(b2Vec2 start, float angle){
    b2PolygonShape beamShape;
    b2FixtureDef beamFixtureDef;
    b2BodyDef myBodyDef;

    beamShape.SetAsBox(0.32f,0.095f); // forma de caja de 2x2
    beamFixtureDef.shape = &beamShape; // le doy la forma de la forma creada
    beamFixtureDef.filter.categoryBits = BEAM;
    beamFixtureDef.filter.maskBits = WORM;
    if(angle < 45.0f)
            beamFixtureDef.friction = 2.5f;

    myBodyDef.type = b2_staticBody; //this will be a static body
    myBodyDef.position.Set(start.x + 0.64f, start.y - 0.095f); //slightly lower position
    myBodyDef.angle = angle * DEGTORAD; //set the starting angle
    b2Body* staticBody = world->CreateBody(&myBodyDef); //add body to world
    staticBody->CreateFixture(&beamFixtureDef); //add fixture to body
}

void BoxWorld::step(){
    float timeStep = 1.0f / 60.0f;  // Paso de tiempo para la simulación (60 FPS)
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    world->Step(timeStep, velocityIterations, positionIterations);
}

b2Vec2 BoxWorld::pixel_to_meter(Vect2D pixel) {
    return b2Vec2(pixel.x * 0.01f, (pixel.y * (-0.01f)) + 50.0f);
}
#include <iostream>
bool BoxWorld::set_map(std::vector<Tile> map) {
    for (auto tile : map) {
        Vect2D position(tile.pos_x, tile.pos_y);
    
        switch(tile.type) {
            case SHORT_BEAM:
                create_short_beam(pixel_to_meter(position), tile.angle);
                std::cout << "creamos una corta" << std::endl;
                break;
            case LONG_BEAM:
                create_long_beam(pixel_to_meter(position), tile.angle);
                std::cout << "creamos una laaaarga" << std::endl;
                break;
            default:
                return false;
        }
    }
    return true;
}

b2Body* BoxWorld::create_projectile(float x, float y, float restitution, float direction, int category, int mask) {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    b2Vec2 pos = b2Vec2(x,y) + b2Vec2(0.12f - 0.24f*direction, 0.15f);
    myBodyDef.position.Set(pos.x, pos.y);
    myBodyDef.position.Set(pos.x, pos.y);
    b2Body* projectile = world->CreateBody(&myBodyDef);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0.0f, 0.0f); //position, relative to body position
    circleShape.m_radius = 0.1f; //radius
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
    myFixtureDef.density = 0.001f;
    myFixtureDef.restitution = restitution;
    myFixtureDef.filter.categoryBits = category;
    myFixtureDef.filter.maskBits = mask;
    projectile->CreateFixture(&myFixtureDef); //add a fixture to the body

    return projectile;
}
