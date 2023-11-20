#include "GameWorldUpdate.h"

#include "ServerProtocol.h"

GameWorldUpdate::GameWorldUpdate(const std::map<int, Point>& positions) {
    this->positions = positions;
}

char GameWorldUpdate::get_sent_by(ServerProtocol& prot) { return prot.send_WorldUpdate(*this); }

GameWorldUpdate::~GameWorldUpdate() {}
