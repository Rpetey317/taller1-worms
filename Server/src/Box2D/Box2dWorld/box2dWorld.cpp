#include "box2dWorld.h"
#include "../Box2DWeapons/WeaponsHeaders.h"
#include "../Box2dPlayer/box2dPlayer.h"

#define DEGTORAD -0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define SHORT_BEAM '0'
#define LONG_BEAM '1'
#define NEW_WORM '2'

#define RIGHT 0
#define LEFT 1

#define BAT_LENGTH 0.5f

BoxWorld::BoxWorld(std::list<Box2DPlayer>& worm) : configurator(), worms(worm), contacts(10000) {
    initialize_world();
}

void BoxWorld::initialize_world() {
    // creo el mundo
    b2Vec2 gravity(0.0f, configurator.get_box2D_configuration().gravity);  // se le da el valor de gravedad que querramos
    world = new b2World(gravity);
    float height = configurator.get_box2D_configuration().map_height;
    float width = configurator.get_box2D_configuration().map_width;
    float zero = 0.0f;
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
    Box2DPlayer player(id, worm, RIGHT, WORM_STILL, configurator.get_worm_configuration().health);
    std::cout << "creamos un gusano y se lo empuja a la lista" << std::endl; 
    worms.push_back(player);
    std::cout << "se lo empujo a la lista y tiene tamaño " << std::to_string(worms.size()) << std::endl;
    worm->GetUserData().pointer = ((uintptr_t)&player);
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
    boxFixtureDef.density = 1.0f;
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
    myBodyDef.angle = angle * configurator.get_box2D_configuration().deg_to_rad; //set the starting angle
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
    myBodyDef.angle = angle * configurator.get_box2D_configuration().deg_to_rad; //set the starting angle
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
        Box2DPlayer* temp = (Box2DPlayer*)(body->GetUserData().pointer);
        temp->get_hurt(damage);
        printf("aplico una fuerza de (%f, %f) en el cuerpo parado en (%f, %f)\n\n\n\n", (impulseMag * blastDir.x), (impulseMag * blastDir.y), applyPoint.x, applyPoint.y);
        body->ApplyLinearImpulse( impulseMag * blastDir, applyPoint , true);
    }
}


void BoxWorld::fragments() {
    const int numBombs = this->fragment_amount;
    const float angleIncrement = b2_pi / numBombs;
    for (int i = 0; i < numBombs; i++) {
        float angle = i * angleIncrement;
        b2Vec2 bombPosition = contactCenter + b2Vec2(cosf(angle), sinf(angle));
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
        b2Vec2 Vector = b2Vec2( 0.000001f*cosf(angle), 0.000001f*sinf(angle) );
        fragment->ApplyLinearImpulseToCenter( Vector , true );
        fragment->SetBullet(true);
        projectiles.push_back(fragment);
        int type = FRAGMENT;
        Box2DPlayer bullet(type, fragment);
        fragment->GetUserData().pointer = ((uintptr_t)&bullet);
    }
}

void BoxWorld::air_missiles(){
    int half_amount = configurator.get_weapons_configuration().air_strike.ammount_of_fragments/2;
    for (int i = -half_amount; i < half_amount; i++) {
        b2Vec2 bombPosition = b2Vec2(contactCenter.x + i*0.5f, 70.0f + i*0.5f);
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody;
        b2Vec2 pos = bombPosition;
        myBodyDef.position.Set(pos.x, pos.y);
        b2Body* missile = world->CreateBody(&myBodyDef);
        b2CircleShape circleShape;
        circleShape.m_p.Set(0.0f, 0.0f); //position, relative to body position
        circleShape.m_radius = 0.05f; //radius
        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
        myFixtureDef.density = 0.1f;
        myFixtureDef.restitution = configurator.get_weapons_configuration().air_strike.restitution;
        myFixtureDef.filter.categoryBits = AIR_MISSLE;
        myFixtureDef.filter.maskBits = WORM | BEAM;
        missile->CreateFixture(&myFixtureDef); //add a fixture to the body
        missile->SetBullet(true);
        projectiles.push_back(missile);
        int type = AIR_MISSLE;
        Box2DPlayer bullet(type, missile);
        missile->GetUserData().pointer = ((uintptr_t)&bullet);
    }
}

void BoxWorld::blast(){
    printf("check center at (%f, %f) explota con fuerza: %f y radio: %f\n", contactCenter.x, contactCenter.y, blastPower, blastRadius);
    box2dQueryCallback queryCallback;
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
}

void BoxWorld::execute_checks(){
    if (check_blast){
        blast();
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
}

void BoxWorld::clean_projectiles(bool full_clean){
    for (auto it = projectiles_to_remove.begin(); it != projectiles_to_remove.end(); ++it) {
        b2Body* projectile = *it;
        world->DestroyBody(projectile);
        projectiles_to_remove.erase(it);
    }
    if(full_clean){
        for (auto it = projectiles.begin(); it != projectiles.end(); ++it) {
            b2Body* projectile = *it;
            world->DestroyBody(projectile);
            projectiles.erase(it);
        }
    }
}


void BoxWorld::step(){
    float timeStep = 1.0f / configurator.get_box2D_configuration().time_step;  // Paso de tiempo para la simulación (60 FPS)
    int32 velocityIterations = configurator.get_box2D_configuration().velocity_iterations;
    int32 positionIterations = configurator.get_box2D_configuration().position_iterations;
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
    this->clean_projectiles(false);
}

void BoxWorld::PostSolve(){
    b2Contact* contact;
    while(contacts.try_pop(contact)){
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
        int a = fixtureA->GetFilterData().categoryBits;
        int b = fixtureB->GetFilterData().categoryBits;
        if(!timer_allows)
            continue;
        if ( (a == WORM || a == BEAM) && b == BAZOOKA ) {
            contactSolver(contact, configurator.get_weapons_configuration().bazooka.radius, configurator.get_weapons_configuration().bazooka.damage, fixtureB);
        }
        else if ( (b == BEAM || b == WORM) && a == BAZOOKA ) {
            contactSolver(contact, configurator.get_weapons_configuration().bazooka.radius, configurator.get_weapons_configuration().bazooka.damage, fixtureA);
        }

        if ( (a == WORM || a == BEAM) && b == MORTAR ) {
            contactSolver(contact, configurator.get_weapons_configuration().mortar.radius, configurator.get_weapons_configuration().mortar.damage, fixtureB);
            this->fragment_amount = configurator.get_weapons_configuration().mortar.ammount_of_fragments;
            this->fragment_damage = configurator.get_weapons_configuration().mortar.damage_of_fragments;
            this->fragment_radius = configurator.get_weapons_configuration().mortar.radius_of_fragments;
            create_fragments = true;
        }
        else if ( (b == BEAM || b == WORM) && a == MORTAR ) {
            contactSolver(contact, configurator.get_weapons_configuration().mortar.radius, configurator.get_weapons_configuration().mortar.damage, fixtureA);
            this->fragment_amount = configurator.get_weapons_configuration().mortar.ammount_of_fragments;
            this->fragment_damage = configurator.get_weapons_configuration().mortar.damage_of_fragments;
            this->fragment_radius = configurator.get_weapons_configuration().mortar.radius_of_fragments;
            create_fragments = true;
        }

        if ( (a == WORM || a == BEAM) && b == FRAGMENT ) {
            contactSolver(contact, this->fragment_damage, this->fragment_radius, fixtureB);
        }
        else if ( (b == BEAM || b == WORM) && a == FRAGMENT ) {
            contactSolver(contact, this->fragment_damage, this->fragment_radius, fixtureA);
        }

        if ( (a == WORM || a == BEAM) && b == GREEN_GRANADE ) {
            contactSolver(contact, configurator.get_weapons_configuration().green_grenade.radius, configurator.get_weapons_configuration().green_grenade.damage, fixtureB);
        }
        else if ( (b == BEAM || b == WORM) && a == GREEN_GRANADE ) {
            contactSolver(contact, configurator.get_weapons_configuration().green_grenade.radius, configurator.get_weapons_configuration().green_grenade.damage, fixtureA);
        }

        if ( (a == WORM || a == BEAM) && b == RED_GRANADE ) {
            contactSolver(contact, configurator.get_weapons_configuration().red_grenade.radius, configurator.get_weapons_configuration().red_grenade.damage, fixtureB);
            this->fragment_amount = configurator.get_weapons_configuration().red_grenade.ammount_of_fragments;
            this->fragment_damage = configurator.get_weapons_configuration().red_grenade.damage_of_fragments;
            this->fragment_radius = configurator.get_weapons_configuration().red_grenade.radius_of_fragments;
            create_fragments = true;
        }
        else if ( (b == BEAM || b == WORM) && a == RED_GRANADE ) {
            contactSolver(contact, configurator.get_weapons_configuration().red_grenade.radius, configurator.get_weapons_configuration().red_grenade.damage, fixtureA);
            this->fragment_amount = configurator.get_weapons_configuration().red_grenade.ammount_of_fragments;
            this->fragment_damage = configurator.get_weapons_configuration().red_grenade.damage_of_fragments;
            this->fragment_radius = configurator.get_weapons_configuration().red_grenade.radius_of_fragments;
            create_fragments = true;
        }

        if ( (a == WORM || a == BEAM) && b == BANANA ) {
            contactSolver(contact, configurator.get_weapons_configuration().banana.radius, configurator.get_weapons_configuration().banana.damage, fixtureB);
        }
        else if ( (b == BEAM || b == WORM) && a == BANANA ) {
            contactSolver(contact, configurator.get_weapons_configuration().banana.radius, configurator.get_weapons_configuration().banana.damage, fixtureA);
        }

        if ( (a == WORM || a == BEAM) && b == HOLY_GRANADE ) {
            contactSolver(contact, configurator.get_weapons_configuration().holy_grenade.radius, configurator.get_weapons_configuration().holy_grenade.damage, fixtureB);
        }
        else if ( (b == BEAM || b == WORM) && a == HOLY_GRANADE ) {
            contactSolver(contact, configurator.get_weapons_configuration().holy_grenade.radius, configurator.get_weapons_configuration().holy_grenade.damage, fixtureA);
        }

        if ( (a == WORM || a == BEAM) && b == AIR_MISSLE ) {
            contactSolver(contact, configurator.get_weapons_configuration().air_strike.radius_of_fragments, configurator.get_weapons_configuration().air_strike.damage_of_fragments, fixtureB);
        }
        else if ( (b == BEAM || b == WORM) && a == AIR_MISSLE ) {
            contactSolver(contact, configurator.get_weapons_configuration().air_strike.radius_of_fragments, configurator.get_weapons_configuration().air_strike.damage_of_fragments, fixtureA);
        }

        if ( (a == WORM || a == BEAM) && b == DYNAMITE ) {
            contactSolver(contact, configurator.get_weapons_configuration().dynamite.radius, configurator.get_weapons_configuration().dynamite.damage, fixtureB);
        }
        else if ( (b == BEAM || b == WORM) && a == DYNAMITE ) {
            contactSolver(contact, configurator.get_weapons_configuration().dynamite.radius, configurator.get_weapons_configuration().dynamite.damage, fixtureA);
        }
    }
}

b2Vec2 BoxWorld::pixel_to_meter(Vect2D pixel) {
    return b2Vec2(pixel.x * configurator.get_box2D_configuration().pixel_to_meters, (pixel.y * (-configurator.get_box2D_configuration().pixel_to_meters)) + 50.0f);
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
                create_worm(pixel_to_meter(position).x, pixel_to_meter(position).y, worms.size() + 1);
                std::cout << "creamos un gusano" << std::endl;
                break;
            default:
                return false;
        }
    }
    return true;
}

b2Body* BoxWorld::create_projectile(float x, float y, float restitution, float direction, int category, int mask, bool set_timer, int type) {
    this->timer_allows = set_timer;
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    b2Vec2 pos = b2Vec2(x,y) + b2Vec2(0.16f - 0.32f*direction, 0.15f);
    myBodyDef.position.Set(pos.x, pos.y);
    myBodyDef.position.Set(pos.x, pos.y);
    b2Body* projectile = world->CreateBody(&myBodyDef);
    b2CircleShape circleShape;
    circleShape.m_p.Set(0.0f, 0.0f); //position, relative to body position
    circleShape.m_radius = 0.05f; //radius
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
    myFixtureDef.density = 0.002f;
    myFixtureDef.restitution = restitution;
    myFixtureDef.filter.categoryBits = category;
    myFixtureDef.filter.maskBits = mask;
    projectile->CreateFixture(&myFixtureDef); //add a fixture to the body
    std::cout << "creamos un proyectil en la posicion " << std::to_string(pos.x) << " " << std::to_string(pos.y) << std::endl;
    projectiles.push_back(projectile);
    Box2DPlayer bullet(type, projectile);
    projectile->GetUserData().pointer = ((uintptr_t)&bullet);
    return projectile;
}

void BoxWorld::air_strike(Vect2D position){
    this->contactCenter = pixel_to_meter(position);
    this->air_check = true;
    this->execute_checks();
}

void BoxWorld::teleport(Vect2D position, b2Body* current){
    b2Vec2 teleport_position = pixel_to_meter(position);
    bool valid_position = true;
    for(b2Body* body = this->world->GetBodyList(); body != NULL; body = body->GetNext()){
        if(body->GetFixtureList()->GetFilterData().categoryBits == BEAM){
            if(body->GetFixtureList()->TestPoint(teleport_position)){
                valid_position = false;
                break;
            }
        }
    }
    if(valid_position)
        current->SetTransform(b2Vec2(teleport_position.x, teleport_position.y + 0.16f), 0.0f);
}

void BoxWorld::dynamite(b2Vec2 position){
    this->contactCenter = position;
    this->check_blast = true;
    this->execute_checks();
}

void BoxWorld::baseball_bat(b2Body* current, float angle, float power, float direction){
    float batting_angle;
    if (direction == 0) {
        batting_angle = 90 - angle;
    } else batting_angle = 270 + angle;
    batting_angle = batting_angle * configurator.get_box2D_configuration().deg_to_rad;    
    b2Vec2 rayDir(sinf(batting_angle), cosf(batting_angle));
    b2Vec2 center(current->GetPosition().x, current->GetPosition().y);
    rayDir.y = -rayDir.y;    
    b2Vec2 p2 = center + configurator.get_weapons_configuration().baseball.radius * rayDir;
    box2dRayCastCallback callback;
    this->world->RayCast(&callback, center, p2);
    if (callback.body) {
        int body_type = callback.body->GetFixtureList()->GetFilterData().categoryBits;
        if (body_type == WORM) {   
            Box2DPlayer* temp = (Box2DPlayer*)(callback.body->GetUserData().pointer);
            if (temp) {
                temp->get_hurt(configurator.get_weapons_configuration().baseball.damage);
                temp->get_body()->ApplyLinearImpulseToCenter( b2Vec2( 0.001f*cosf(batting_angle), 0.001f*sinf(batting_angle) ) , true );
            }
        }
    }
}

void BoxWorld::set_teams(int worm_id, int player_id){
    for (auto& worm : worms) {
        if(worm.get_id() == worm_id){
            worm.set_team_id(player_id);
            return;
        }
    }
}

BoxWorld::~BoxWorld() {
    delete world;
    delete contact_listener;
}
