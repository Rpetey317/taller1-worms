#ifndef EVENT_H_
#define EVENT_H_

#include <list>
#include <map>
#include <string>
#include <vector>

#include "Vect2D.h"
#include "WeaponDTO.h"
#include "Worm.h"

class ClientProtocol;
class EventProcessor;
// #include "../EventProcessor/EventProcessor.h"


class Event {
protected:
    int id;

    explicit Event(const int& _id): id(_id) {}

public:
    int get_id() { return this->id; }

    virtual void get_processed_by(EventProcessor& eventProcessor) = 0;

    virtual std::map<int, Vect2D> get_worm_positions() { return std::map<int, Vect2D>(); }

    virtual std::map<int, Worm> get_worms() { return std::map<int, Worm>(); }

    virtual std::list<WeaponDTO> get_weapons() { return std::list<WeaponDTO>(); }

    virtual bool is_new_player() { return false; }

    virtual std::string get_type_proyectile() { return "NULL"; }

    virtual int get_proyectile_angle() { return 0; }

    virtual Vect2D get_proyectile_position() { return Vect2D(0, 0); }

    virtual bool proyectile_got_exploded() { return false; }

    virtual int get_duration() { return 0; }  //

    virtual int get_player_turn() { return -1; }

    virtual ~Event() = default;
};

#endif  // EVENT_H_
