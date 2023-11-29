#include "Box2DMsg.h"

#include <memory>

#include "Game.h"

Box2DMsg::Box2DMsg(const int& _id, const int& _cmd): Message(_id), command(_cmd) {}

std::shared_ptr<Update> Box2DMsg::get_processed_by(Game& game) { return game.process_box2d(*this); }

int& Box2DMsg::get_cmd() { return this->command; }
