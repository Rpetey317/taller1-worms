#ifndef MAPUPDATE_H
#define MAPUPDATE_H

#include <list>
#include <map>
#include <string>
#include <vector>

#include "../Event.h"

#include "WeaponDTO.h"
#include "Worm.h"

class MapUpdate: public Event {
    // private:
    std::map<int, Worm> worms;
    std::list<WeaponDTO> weapons;

public:
    MapUpdate(const std::map<int, Worm>& worms, const std::list<WeaponDTO>& weapons);

    explicit MapUpdate(const std::map<int, Worm>& worms);

    void get_processed_by(EventProcessor& eventProcessor) override;

    std::map<int, Vect2D> get_worm_positions() override;

    std::map<int, Worm> get_worms() override;

    std::list<WeaponDTO> get_weapons() override;
};

#endif  // MAPUPDATE_H
