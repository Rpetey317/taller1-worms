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
    explicit MapUpdate(const std::map<int, Point>& positions);

    void get_processed_by(EventProcessor& eventProcessor) override;

    std::map<int, Point> get_worm_positions();
};

#endif  // MAPUPDATE_H
