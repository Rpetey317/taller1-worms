#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include <vector>

class ClientProtocol;

class Event {
protected:
    int id;
    bool valid;

    explicit Event(const int& _id): id(_id), valid(true) {}

public:
    int get_id() { return this->id; }

    bool is_valid() { return this->valid; }

    virtual ~Event() = default;
};

#endif  // EVENT_H_