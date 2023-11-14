#ifndef PLAYERPOSITION_H_
#define PLAYERPOSITION_H_

#include <string>
#include <vector>

#include "../Event.h"


class PlayerPosition: public Event {
    // private:
    int pos_x;
    int pos_y;

public:
    PlayerPosition(const int& player_id, const int& pos_x, const int& pos_y);

    void get_processed_by(EventProcessor& eventProcessor) override;

    int get_position_x();

    int get_position_y();
};

#endif  // PLAYERPOSITION_H_
