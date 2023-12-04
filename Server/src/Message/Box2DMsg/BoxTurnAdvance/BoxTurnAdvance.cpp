#include "BoxTurnAdvance.h"

BoxTurnAdvance::BoxTurnAdvance(const int& new_pl_id): Box2DMsg(new_pl_id, 0) {}

BoxTurnAdvance::~BoxTurnAdvance() {}

int BoxTurnAdvance::get_cmd() { return COMMAND_NEXT; }
