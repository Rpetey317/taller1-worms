#include "BoxJump.h"

#include <memory>
#include <utility>

#include "Box2dManager/box2dManager.h"

BoxJump::BoxJump(bool _is_fw, int _id): Box2DMsg(_id, 0), forward(_is_fw) {}

std::shared_ptr<Message> BoxJump::jump_fw(int id) {
    return std::shared_ptr<Message>(new BoxJump(true, id));
}

std::shared_ptr<Message> BoxJump::jump_bw(int id) {
    return std::shared_ptr<Message>(new BoxJump(false, id));
}

int BoxJump::get_cmd() { return this->forward ? COMMAND_JUMP_FOWARD : COMMAND_JUMP_BACKWARD; }

bool BoxJump::is_forward() const { return this->forward; }
