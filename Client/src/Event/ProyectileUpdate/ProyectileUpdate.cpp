#include "ProyectileUpdate.h"

#include <map>

#include "../EventProcessor/EventProcessor.h"

ProyectileUpdate::ProyectileUpdate(const int& player_id, std::string type, Vect2D position, int angle, bool exploded):
        Event(player_id), type_proyectile(type), position(position), angle(angle), exploded(exploded) {}

void ProyectileUpdate::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.proccess_proyectile_update(*this);
}

std::string ProyectileUpdate::get_type_proyectile() { return this->type_proyectile; }

int ProyectileUpdate::get_angle() { return this->angle; }

Vect2D ProyectileUpdate::get_position() { return this->position; }

bool ProyectileUpdate::got_exploded() { return this->exploded; }
