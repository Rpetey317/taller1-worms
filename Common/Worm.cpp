#include "Worm.h"

Worm::Worm() {}

Worm::Worm(Vect2D position, int state, int id, int player_id, int health_points,
           std::string map_name):
        position(position),
        state(state),
        id(id),
        player_id(player_id),
        health_points(health_points),
        map_name(map_name) {}

Worm::Worm(Vect2D position, int state, int id, int player_id, int health_points):
        position(position),
        state(state),
        id(id),
        player_id(player_id),
        health_points(health_points) {}

Worm::Worm(Vect2D position, int state, int id, int health_points):
        position(position), state(state), id(id), health_points(health_points) {}

Worm::Worm(Vect2D position, int state, int id):
        position(position), state(state), id(id), health_points(100) {}

Worm::Worm(Vect2D position, int id): position(position), state(0), id(id), health_points(100) {}

Worm::~Worm() {}
