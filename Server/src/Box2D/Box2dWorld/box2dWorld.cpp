#include "box2dWorld.h"
#include "../Box2DWeapons/WeaponsHeaders.h"
#include "../Box2dPlayer/box2dPlayer.h"

#define DEGTORAD -0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define SHORT_BEAM '0'
#define LONG_BEAM '1'
#define NEW_WORM '2'

BoxWorld::BoxWorld(std::list<Box2DPlayer>& worm) : worms(worm), contacts(10000) {
    initialize_world();
}

void BoxWorld::initialize_world() {
    // creo el mundo
    b2Vec2 gravity(0.0f, -9.8f);  // se le da el valor de gravedad que querramos
    world = new b2World(gravity);
    float height = 50.0f;
    float width = 200.0f;
    float zero = -0.15f;
    contact_listener = new box2dContactListener(contacts);
    world->SetContactListener(contact_listener);
    create_ground(b2Vec2(zero,zero), b2Vec2(width,zero), b2Vec2(zero,height), b2Vec2(width, height)); 
}

b2Body* BoxWorld::create_worm(float x, float y, int id) {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; 
    myBodyDef.position.Set(x, y); 
    myBodyDef.angle = 0; 
    b2Body* worm = world->CreateBody(&myBodyDef);
    Box2DPlayer player(id, worm);
    std::cout << "creamos un gusano y se lo empuja a la lista" << std::endl; 
    worms.push_back(player);
    std::cout << "se lo empujo a la lista y tiene tamaño " << std::to_string(worms.size()) << std::endl;
    myBodyDef.userData.pointer = ((uintptr_t)&player);
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
    boxFixtureDef.density = 2.5f;
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

void applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower, float blastRadius) {
    b2Vec2 blastDir = applyPoint - blastCenter;
    float distance = blastDir.Normalize();
    float damage = blastPower * ((-distance/blastRadius) + 1) * 1000;
    printf("el dano es %f\n", damage);
    if(blastDir.y > 0) {
        blastDir.y = -blastDir.y;
    }
	if(distance <= 1) {
        distance = 1;
    }
	float invDistance = 1/distance;
	float impulseMag = (blastPower/2) * invDistance;
    if(body->GetFixtureList()->GetFilterData().categoryBits == WORM){
        printf("aplico una fuerza de (%f, %f) en el cuerpo parado en (%f, %f)\n\n\n\n", (impulseMag * blastDir.x), (impulseMag * blastDir.y), applyPoint.x, applyPoint.y);
        body->ApplyLinearImpulse( impulseMag * blastDir, applyPoint , true);
    }
}


void BoxWorld::fragments() {
    const int numBombs = 6;
    const float angleIncrement = b2_pi / numBombs;
    for (int i = 0; i < numBombs; i++) {
        float angle = i * angleIncrement;
        b2Vec2 bombPosition = contactCenter + b2Vec2(cos(angle), sin(angle));
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody;
        b2Vec2 pos = bombPosition;
        myBodyDef.position.Set(pos.x, pos.y);
        b2Body* fragment = world->CreateBody(&myBodyDef);
        b2CircleShape circleShape;
        circleShape.m_p.Set(0.0f, 0.0f); //position, relative to body position
        circleShape.m_radius = 0.01f; //radius
        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
        myFixtureDef.density = 0.1f;
        myFixtureDef.restitution = 0.0f;
        myFixtureDef.filter.categoryBits = FRAGMENT;
        myFixtureDef.filter.maskBits = WORM | BEAM;
        fragment->CreateFixture(&myFixtureDef); //add a fixture to the body
        b2Vec2 Vector = b2Vec2( 0.000001f*cos(angle), 0.000001f*sin(angle) );
        fragment->ApplyLinearImpulseToCenter( Vector , true );
        fragment->SetBullet(true);
    }
}

void BoxWorld::air_missiles(){
    for (int i = -3; i < 3; i++) {
        b2Vec2 bombPosition = b2Vec2(contactCenter.x + i*0.5f, 70.0f + i*0.5f);
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody;
        b2Vec2 pos = bombPosition;
        myBodyDef.position.Set(pos.x, pos.y);
        b2Body* missile = world->CreateBody(&myBodyDef);
        b2CircleShape circleShape;
        circleShape.m_p.Set(0.0f, 0.0f); //position, relative to body position
        circleShape.m_radius = 0.1f; //radius
        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
        myFixtureDef.density = 0.1f;
        myFixtureDef.restitution = 0.0f;
        myFixtureDef.filter.categoryBits = AIR_MISSLE;
        myFixtureDef.filter.maskBits = WORM | BEAM;
        missile->CreateFixture(&myFixtureDef); //add a fixture to the body
        missile->SetBullet(true);
    }
}

void BoxWorld::execute_checks(){
    if (check_blast){
        printf("check center at (%f, %f) explota con fuerza: %f y radio: %f\n", contactCenter.x, contactCenter.y, blastPower, blastRadius);
        MyQueryCallback queryCallback;
        b2AABB aabb;
        aabb.lowerBound = contactCenter - b2Vec2( blastRadius, blastRadius );
        aabb.upperBound = contactCenter + b2Vec2( blastRadius, blastRadius );
        world->QueryAABB( &queryCallback, aabb );
        
        for (size_t i = 0; i < queryCallback.foundBodies.size(); i++) {
            b2Body* body = queryCallback.foundBodies[i];
            b2Vec2 bodyCom = body->GetWorldCenter();
            if ( (bodyCom - contactCenter).Length() >= blastRadius )
                continue;
            printf("encontro un cuerpo para aplicar la fuerza\n");
            
            applyBlastImpulse(body, contactCenter, bodyCom, blastPower, blastRadius);
        }

        check_blast = false;
    }
    if(create_fragments){
        fragments();
        create_fragments = false;
    }
    if(air_check){
        air_missiles();
        air_check = false;
    }
    if(check_teleport){
        // current->SetTransform(b2Vec2(center.x, center.y + 0.16f), 0.0f);
        check_teleport = false;
    }
}

void BoxWorld::clean_projectiles(){
    for (auto it = projectiles_to_remove.begin(); it != projectiles_to_remove.end(); ++it) {
        b2Body* projectile = *it;
        world->DestroyBody(projectile);
    }
    for (auto it = projectiles.begin(); it != projectiles.end(); ++it) {
        b2Body* projectile = *it;
        if(projectile->GetLinearVelocity().y == 0.0f && projectile->GetLinearVelocity().x == 0.0f){
            world->DestroyBody(projectile);
            projectiles.erase(it);
        }
    }
}

void BoxWorld::step(){
    float timeStep = 1.0f / 30.0f;  // Paso de tiempo para la simulación (60 FPS)
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    world->Step(timeStep, velocityIterations, positionIterations);
    this->PostSolve();
}

void BoxWorld::contactSolver(b2Contact* contact, float radius, float power,  b2Fixture* fixture){
    printf("contactSolver\n");
    projectiles_to_remove.push_back(fixture->GetBody());
    blastRadius = radius;
    blastPower = power;
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    contactCenter = worldManifold.points[0];
    printf("center at (%f, %f)\n", contactCenter.x, contactCenter.y);
    check_blast = true;    
    this->execute_checks();
    this->clean_projectiles();
}

void BoxWorld::PostSolve(){
    b2Contact* contact;
    while(contacts.try_pop(contact)){
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
        int a = fixtureA->GetFilterData().categoryBits;
        int b = fixtureB->GetFilterData().categoryBits;

        if ( a == WORM && b == BAZOOKA ) {
            contactSolver(contact, 2.0f, 0.05f, fixtureB);
        }
        else if ( b == WORM && a == BAZOOKA ) {
            contactSolver(contact, 2.0f, 0.05f, fixtureA);
        }
        else if ( a == BEAM && b == BAZOOKA ) {
            contactSolver(contact, 2.0f, 0.05f, fixtureB);
        }
        else if ( b == BEAM && a == BAZOOKA ) {
            contactSolver(contact, 2.0f, 0.05f, fixtureA);
        }

        if ( a == WORM && b == MORTAR ) {
            contactSolver(contact, 2.0f, 0.05f, fixtureB);
            create_fragments = true;
        }
        else if ( b == WORM && a == MORTAR ) {
            contactSolver(contact, 2.0f, 0.05f, fixtureA);
            create_fragments = true;
        }
        else if ( a == BEAM && b == MORTAR ) {
            contactSolver(contact, 2.0f, 0.05f, fixtureB);
            create_fragments = true;
        }
        else if ( b == BEAM && a == MORTAR ) {
            contactSolver(contact, 2.0f, 0.05f, fixtureA);
            create_fragments = true;
        }

        if ( a == WORM && b == FRAGMENT ) {
            contactSolver(contact, 2.0f, 0.01f, fixtureB);
        }
        else if ( b == WORM && a == FRAGMENT ) {
            contactSolver(contact, 2.0f, 0.01f, fixtureA);
        }
        else if ( a == BEAM && b == FRAGMENT ) {
            contactSolver(contact, 2.0f, 0.01f, fixtureB);
        }
        else if ( b == BEAM && a == FRAGMENT ) {
            contactSolver(contact, 2.0f, 0.01f, fixtureA);
        }

        if ( a == WORM && b == GREEN_GRANADE ) {
            contactSolver(contact, 2.0f, 0.03f, fixtureB);
        }
        else if ( b == WORM && a == GREEN_GRANADE ) {
            contactSolver(contact, 2.0f, 0.03f, fixtureA);
        }
        else if ( a == BEAM && b == GREEN_GRANADE ) {
            contactSolver(contact, 2.0f, 0.03f, fixtureB);
        }
        else if ( b == BEAM && a == GREEN_GRANADE ) {
            contactSolver(contact, 2.0f, 0.03f, fixtureA);
        }

        if ( a == WORM && b == RED_GRANADE ) {
            contactSolver(contact, 2.0f, 0.03f, fixtureB);
            create_fragments = true;
        }
        else if ( b == WORM && a == RED_GRANADE ) {
            contactSolver(contact, 2.0f, 0.03f, fixtureA);
            create_fragments = true;
        }
        else if ( a == BEAM && b == RED_GRANADE ) {
            contactSolver(contact, 2.0f, 0.03f, fixtureB);
            create_fragments = true;
        }
        else if ( b == BEAM && a == RED_GRANADE ) {
            contactSolver(contact, 2.0f, 0.03f, fixtureA);
            create_fragments = true;
        }

        if ( a == WORM && b == BANANA ) {
            contactSolver(contact, 4.0f, 0.07f, fixtureB);
        }
        else if ( b == WORM && a == BANANA ) {
            contactSolver(contact, 4.0f, 0.07f, fixtureA);
        }
        else if ( a == BEAM && b == BANANA ) {
            contactSolver(contact, 4.0f, 0.07f, fixtureB);
        }
        else if ( b == BEAM && a == BANANA ) {
            contactSolver(contact, 4.0f, 0.07f, fixtureA);
        }

        if ( a == WORM && b == HOLY_GRANADE ) {
            contactSolver(contact, 8.0f, 0.11f, fixtureB);
        }
        else if ( b == WORM && a == HOLY_GRANADE ) {
            contactSolver(contact, 8.0f, 0.11f, fixtureA);
        }
        else if ( a == BEAM && b == HOLY_GRANADE ) {
            contactSolver(contact, 8.0f, 0.11f, fixtureB);
        }
        else if ( b == BEAM && a == HOLY_GRANADE ) {
            contactSolver(contact, 8.0f, 0.11f, fixtureA);
        }
        
        if ( a == WORM && b == AIR_STRIKE ) {
            contactSolver(contact, 0.0f, 0.0f, fixtureB);
            air_check = true;
        }
        else if ( b == WORM && a == AIR_STRIKE ) {
            contactSolver(contact, 0.0f, 0.0f, fixtureA);
            air_check = true;
        }
        else if ( a == BEAM && b == AIR_STRIKE ) {
            contactSolver(contact, 0.0f, 0.0f, fixtureB);
            air_check = true;
        }
        else if ( b == BEAM && a == AIR_STRIKE ) {
            contactSolver(contact, 0.0f, 0.0f, fixtureA);
            air_check = true;
        }

        if ( a == WORM && b == AIR_MISSLE ) {
            contactSolver(contact, 2.0f, 0.04f, fixtureB);
        }
        else if ( b == WORM && a == AIR_MISSLE ) {
            contactSolver(contact, 2.0f, 0.04f, fixtureA);
        }
        else if ( a == BEAM && b == AIR_MISSLE ) {
            contactSolver(contact, 2.0f, 0.04f, fixtureB);
        }
        else if ( b == BEAM && a == AIR_MISSLE ) {
            contactSolver(contact, 2.0f, 0.04f, fixtureA);
        }

        if ( a == WORM && b == TELEPORT ) {
            contactSolver(contact, 0.0f, 0.0f, fixtureB);
            check_teleport = true;
        }
        else if ( b == WORM && a == TELEPORT ) {
            contactSolver(contact, 0.0f, 0.0f, fixtureA);
            check_teleport = true;
        }
        else if ( a == BEAM && b == TELEPORT ) {
            contactSolver(contact, 0.0f, 0.0f, fixtureB);
            check_teleport = true;
        }
        else if ( b == BEAM && a == TELEPORT ) {
            contactSolver(contact, 0.0f, 0.0f, fixtureA);
            check_teleport = true;
        }
    }
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
                std::cout << "creamos una larga" << std::endl;
                break;
            case NEW_WORM:
                create_worm(pixel_to_meter(position).x, pixel_to_meter(position).y, worms.size());
                std::cout << "creamos un gusano" << std::endl;
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
    b2Vec2 pos = b2Vec2(x,y) + b2Vec2(0.16f - 0.32f*direction, 0.15f);
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
    projectiles.push_back(projectile);
    return projectile;
}

BoxWorld::~BoxWorld() {
    delete world;
    delete contact_listener;
}
