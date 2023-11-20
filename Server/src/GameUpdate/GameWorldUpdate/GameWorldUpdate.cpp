#include "GameWorldUpdate.h"

GameWorldUpdate::GameWorldUpdate(const std::map<int, std::vector<int>>& positions) {
    this->positions = positions;
}

char GameWorldUpdate::get_sent_by(ServerProtocol& prot) {
    return prot.send_WorldUpdate(*this);
}
