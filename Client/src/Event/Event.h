#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include <vector>

class ClientProtocol;
class EventProcessor;
// #include "../EventProcessor/EventProcessor.h"

class Event {
protected:
    int id;
    bool valid;

    explicit Event(const int& _id): id(_id), valid(true) {}

public:
    int get_id() { return this->id; }

    virtual void get_processed_by(EventProcessor& eventProcessor) = 0;

    bool is_valid() { return this->valid; }

    virtual ~Event() = default;
};

#endif  // EVENT_H_