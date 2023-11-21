#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include <vector>
#include <map>

#include "Point.h"

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

    virtual std::map<int, Point> get_worm_positions() = 0;

    virtual ~Event() = default;
};

#endif  // EVENT_H_
