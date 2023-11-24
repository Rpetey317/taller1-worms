#ifndef MAPUPDATE_H
#define MAPUPDATE_H

#include <map>
#include <string>
#include <vector>

#include "../Event.h"

#include "Vect2D.h"

class MapUpdate: public Event {
    // private:
    std::map<int, Vect2D> worm_positions;

public:
    explicit MapUpdate(const std::map<int, Vect2D>& positions);

    void get_processed_by(EventProcessor& eventProcessor) override;

    std::map<int, Vect2D> get_worm_positions() override;

    bool is_new_player() override;
};

#endif  // MAPUPDATE_H
