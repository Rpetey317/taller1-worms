#include "MapUpdate.h"

#include "../EventProcessor/EventProcessor.h"

MapUpdate::MapUpdate(const std::map<int, Worm>& worms, const std::map<int, WeaponDTO>& weapons):
        Event(0), worms(worms), weapons(weapons) {}

MapUpdate::MapUpdate(const std::map<int, Worm>& worms): Event(0), worms(worms) {}

void MapUpdate::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_map_update(*this);
}

std::map<int, Vect2D> MapUpdate::get_worm_positions() {
    std::map<int, Vect2D> worm_positions;

    int amount_players = this->worms.size();
    for (int i = 0; i < amount_players; i++) {
        int player_id = this->worms[i].id;
        worm_positions[player_id] = this->worms[i].position;
    }
    return worm_positions;
}

std::map<int, Worm> MapUpdate::get_worms() { return this->worms; }

std::map<int, WeaponDTO> MapUpdate::get_weapons() { return this->weapons; }
