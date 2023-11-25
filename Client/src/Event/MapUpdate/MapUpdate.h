#ifndef MAPUPDATE_H
#define MAPUPDATE_H

#include <map>
#include <string>
#include <vector>

#include "../Event.h"

#include "Worm.h"

class MapUpdate: public Event {
    // private:
    std::map<int, Worm> worms;

public:
    explicit MapUpdate(const std::map<int, Worm>& positions);

    void get_processed_by(EventProcessor& eventProcessor) override;

    std::map<int, Vect2D> get_worm_positions() override;

    std::map<int, Worm> get_worms() override;

    bool is_new_player() override;
};

#endif  // MAPUPDATE_H
