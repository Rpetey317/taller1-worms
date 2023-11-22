#ifndef PLAYERPOSITION_H_
#define PLAYERPOSITION_H_

#include <string>
#include <vector>

#include "../Event.h"

#include "Vect2D.h"


class PlayerPosition: public Event {
    // private:
    Vect2D position;

public:
    PlayerPosition(const int& player_id, Vect2D position);

    void get_processed_by(EventProcessor& eventProcessor) override;

    std::map<int, Vect2D> get_worm_positions() override;

    bool is_new_player() override;

    Vect2D get_position();
};

#endif  // PLAYERPOSITION_H_
