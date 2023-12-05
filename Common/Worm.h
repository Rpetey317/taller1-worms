#ifndef WORM_H
#define WORM_H

#include <string>

#include "Vect2D.h"

enum _entityCategory {
    BEAM = 0x0001,
    WORM = 0x0002,
    BAZOOKA = 0x0003,
    MORTAR = 0x0004,
    GREEN_GRANADE = 0x0005,
    RED_GRANADE = 0x0006,
    BANANA = 0x0007,
    HOLY_GRANADE = 0x0008,
    AIR_STRIKE = 0x0009,
    FRAGMENT = 0x0010,
    AIR_MISSLE = 0x0011,
    TELEPORT = 0x0012,
    DYNAMITE = 0x0013,
    BASEBALL_BAT = 0x0014,

    WORM_WALKING = 0x0015,
    WORM_FALLING = 0x0016,
    WORM_DEAD = 0x0017,
    WORM_STILL = 0x0018,
};

class Worm {
public:
    Vect2D position;
    int state;
    int id;  // Podria tener esto tmb y quizas simplificar el mapa de <int id_player, Worm>
    int player_id;
    int health_points;
    std::string map_name;
    Worm();

    Worm(Vect2D position, int state, int id, int player_id, int health_points,
         const std::string& map_name);

    Worm(Vect2D position, int state, int id, int player_id, int health_points);

    Worm(Vect2D position, int state, int id, int health_points);

    Worm(Vect2D position, int state, int id);

    Worm(Vect2D position, int id);

    ~Worm();
};

#endif  // WORM_H
