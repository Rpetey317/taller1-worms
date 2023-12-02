#include "ProyectileUpdate.h"

#include <map>

#include "../EventProcessor/EventProcessor.h"

ProyectileUpdate::ProyectileUpdate(const int& player_id, Vect2D position):
        Event(player_id), position(position) {}

void ProyectileUpdate::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.proccess_proyectile_update(*this);
}

std::map<int, Vect2D> ProyectileUpdate::get_worm_positions() { return std::map<int, Vect2D>(); }

std::map<int, Worm> ProyectileUpdate::get_worms() { return std::map<int, Worm>(); }

bool ProyectileUpdate::is_new_player() { return false; }

std::string ProyectileUpdate::get_type_proyectile() { return this->type_proyectile; }

int ProyectileUpdate::get_angle() { return this->angle; }

Vect2D ProyectileUpdate::get_position() { return this->position; }
