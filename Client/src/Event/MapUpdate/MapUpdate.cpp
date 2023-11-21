#include "MapUpdate.h"

#include "../EventProcessor/EventProcessor.h"

MapUpdate::MapUpdate(const std::map<int, Point>& positions): Event(100), worm_positions(positions) {}

void MapUpdate::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_map_update(*this);
}

std::map<int, Point> MapUpdate::get_worm_positions() { return this->worm_positions; }
