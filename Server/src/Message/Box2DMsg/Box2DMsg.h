#ifndef __Box2DMsg_H__
#define __Box2DMsg_H__

#include <memory>

#include "../Message.h"

class BoxManager;

#define COMMAND_STOP 0
#define COMMAND_EXIT -1
#define COMMAND_RIGHT 1
#define COMMAND_LEFT 2
#define COMMAND_JUMP_FOWARD 3
#define COMMAND_JUMP_BACKWARD 4
#define COMMAND_NEXT 5
#define COMMAND_SHOOT 6
#define COMMAND_SPECIAL_SHOOT 7

class Box2DMsg: public Message, public std::enable_shared_from_this<Box2DMsg> {

    int command;

public:
    Box2DMsg(const int& id, const int& cmd);

    std::shared_ptr<Update> get_processed_by(Game& game) override;

    virtual int get_cmd()=0;

    ~Box2DMsg() override = default;
};

#endif  // !__Box2DMsg_H__
