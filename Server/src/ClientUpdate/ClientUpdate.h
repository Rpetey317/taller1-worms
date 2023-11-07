#ifndef __CLIENTUPDATE_H__
#define __CLIENTUPDATE_H__

#include <string>

class GameHandler;
class GameUpdate;

// TODO: make this polymorphic
class ClientUpdate {
protected:
    int id;
    bool valid;

    ClientUpdate(const int& _id): id(_id), valid(true) {}

public:

    int get_id() { return this->id; }

    virtual GameUpdate* get_processed_by(GameHandler& game) = 0;

    bool is_valid() { return this->valid; }

    virtual ~ClientUpdate() = default;
};

#endif  // !__CLIENTUPDATE_H__
