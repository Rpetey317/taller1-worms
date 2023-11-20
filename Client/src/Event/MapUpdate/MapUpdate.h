#ifndef MAPUPDATE_H
#define MAPUPDATE_H

#include <map>
#include <string>
#include <vector>

#include "../Event.h"

#include "Point.h"

class MapUpdate: public Event {
    // private:
    std::map<int, Point> worm_positions;

public:
    MapUpdate(const std::map<int, Point>& positions);

    void get_processed_by(EventProcessor& eventProcessor) override;
};

#endif  // MAPUPDATE_H
