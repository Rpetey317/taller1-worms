#ifndef EVENT_H_
#define EVENT_H_

#include <map>
#include <string>
#include <vector>

#include "Vect2D.h"
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

    virtual std::map<int, Vect2D> get_worm_positions() = 0;

    virtual std::map<int, Worm> get_worms() = 0;

    virtual bool is_new_player() = 0;

    virtual std::string get_type_proyectile() {return "NULL";};

    virtual int get_angle() {return 0;};

    virtual ~Event() = default;
};

#endif  // EVENT_H_
