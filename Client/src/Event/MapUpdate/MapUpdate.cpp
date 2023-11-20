#include "MapUpdate.h"

MapUpdate::MapUpdate(const std::map<int, Point>& positions):
        Event(-1), worm_positions(positions) {}

void MapUpdate::get_processed_by(EventProcessor& eventProcessor) {}
