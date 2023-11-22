#include "MapUpdate.h"

#include "../EventProcessor/EventProcessor.h"

MapUpdate::MapUpdate(const std::map<int, Vect2D>& positions):
        Event(100), worm_positions(positions) {}

void MapUpdate::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_map_update(*this);
}

std::map<int, Vect2D> MapUpdate::get_worm_positions() { return this->worm_positions; }
