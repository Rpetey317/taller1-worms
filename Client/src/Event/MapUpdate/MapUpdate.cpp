#include "MapUpdate.h"

MapUpdate::MapUpdate(const std::map<int, std::vector<int>>& positions): Event(-1), worm_positions(positions) {}

void MapUpdate::get_processed_by(EventProcessor& eventProcessor) {}
