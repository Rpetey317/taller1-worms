#ifndef __CLIENTUPDATE_H__
#define __CLIENTUPDATE_H__

#include <memory>
#include <string>

class Game;
class GameUpdate;

// TODO: make this polymorphic
class ClientUpdate {
protected:
    int id;

    explicit ClientUpdate(const int& _id): id(_id) {}

public:
    int get_id() { return this->id; }

    virtual std::shared_ptr<GameUpdate> get_processed_by(Game& game) = 0;

    virtual bool is_valid() { return true; }

    virtual ~ClientUpdate() = default;
};

#endif  // !__CLIENTUPDATE_H__
