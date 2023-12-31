#ifndef PLAYERPOSITION_H_
#define PLAYERPOSITION_H_

#include <map>
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

    // Vect2D get_position() override;  // No se envia nunca este evento
};

#endif  // PLAYERPOSITION_H_
