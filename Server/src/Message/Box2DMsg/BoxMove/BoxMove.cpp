#include "BoxMove.h"

#include <memory>

#include "Box2dManager/box2dManager.h"

BoxMove::BoxMove(bool _is_right, int _id): Box2DMsg(_id, 0), right(_is_right) {}

std::shared_ptr<Message> BoxMove::move_right(int id) {
    return std::shared_ptr<Message>(new BoxMove(true, id));
}

std::shared_ptr<Message> BoxMove::move_left(int id) {
    return std::shared_ptr<Message>(new BoxMove(false, id));
}

int BoxMove::get_cmd() { return this->is_right() ? COMMAND_RIGHT : COMMAND_LEFT; }

bool BoxMove::is_right() const { return this->right; }
