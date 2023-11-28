#ifndef __Box2DMsg_H__
#define __Box2DMsg_H__

#include <memory>

#include "../Message.h"

class Box2DMsg: public Message {

    int command;

public:
    Box2DMsg(const int& id, const int& cmd);

    std::shared_ptr<GameUpdate> get_processed_by(Game& game) override;

    int& get_cmd();

    ~Box2DMsg() override = default;
};

#endif  // !__Box2DMsg_H__
