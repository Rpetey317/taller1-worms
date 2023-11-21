#ifndef PLAYERPOSITION_H_
#define PLAYERPOSITION_H_

#include <string>
#include <vector>

#include "../Event.h"

#include "Point.h"


class PlayerPosition: public Event {
    // private:
    Point position;

public:
    PlayerPosition(const int& player_id, Point position);

    void get_processed_by(EventProcessor& eventProcessor) override;

    std::map<int, Point> get_worm_positions() override;

    Point get_position();
};

#endif  // PLAYERPOSITION_H_
