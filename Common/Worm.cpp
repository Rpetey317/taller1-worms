#include "Worm.h"

Worm::Worm() {}

Worm::Worm(Vect2D position, int state, int id): position(position), state(state), id(id) {}

Worm::Worm(Vect2D position, int id): position(position), state(0), id(id) {}

Worm::~Worm() {}
