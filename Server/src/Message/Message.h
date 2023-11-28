#ifndef __Message_H__
#define __Message_H__

#include <memory>
#include <string>

class Game;
class GameUpdate;

// TODO: make this polymorphic
class Message {
protected:
    int id;

    explicit Message(const int& _id): id(_id) {}

public:
    int get_id() { return this->id; }

    virtual std::shared_ptr<GameUpdate> get_processed_by(Game& game) = 0;

    virtual bool is_valid() { return true; }

    virtual ~Message() = default;
};

#endif  // !__Message_H__
