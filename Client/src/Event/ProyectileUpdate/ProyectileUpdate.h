#ifndef PROYECTILEUPDATE_H_
#define PROYECTILEUPDATE_H_

#include <map>
#include <string>
#include <vector>

#include "../Event.h"

#include "Vect2D.h"


class ProyectileUpdate: public Event {
    // private:
    std::string type_proyectile;
    Vect2D position;
    int angle;


public:
    ProyectileUpdate(const int& player_id, std::string type, Vect2D position, int angle);

    void get_processed_by(EventProcessor& eventProcessor) override;

    std::map<int, Vect2D> get_worm_positions() override;

    std::map<int, Worm> get_worms() override;

    bool is_new_player() override;

    std::string get_type_proyectile() override;

    int get_angle() override;

    Vect2D get_position();
};

#endif  // PROYECTILEUPDATE_H_
