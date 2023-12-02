#ifndef PROYECTILEUPDATE_H_
#define PROYECTILEUPDATE_H_

#include <map>
#include <string>
#include <vector>

#include "../Event.h"

#include "Vect2D.h"


class ProyectileUpdate: public Event {
private:
    std::string type_proyectile;
    Vect2D position;
    int angle;
    bool exploded;

public:
    ProyectileUpdate(const int& player_id, const std::string& type, Vect2D position, int angle,
                     bool exploded);

    void get_processed_by(EventProcessor& eventProcessor) override;

    std::string get_type_proyectile() override;

    int get_angle() override;

    Vect2D get_position() override;

    bool got_exploded() override;
};

#endif  // PROYECTILEUPDATE_H_
