#ifndef WORM_H
#define WORM_H

#include "Vect2D.h"

class Worm {
public:
    Vect2D position;
    int state;
    int id;  // Podria tener esto tmb y quizas simplificar el mapa de <int id_player, Worm>

    Worm();

    Worm(Vect2D position, int state, int id);

    Worm(Vect2D position, int id);

    ~Worm();
};

#endif  // WORM_H
