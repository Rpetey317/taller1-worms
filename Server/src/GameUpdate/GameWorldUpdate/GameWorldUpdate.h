#ifndef __GAME_WORLD_UPDATE_H__
#define __GAME_WORLD_UPDATE_H__

#include <map>
#include <vector>

#include "Point.h"
#include "../GameUpdate.h"

class GameWorldUpdate: public GameUpdate {

    std::map<int, Point> positions;

public:
    explicit GameWorldUpdate(const std::map<int, Point>& positions);
    char get_sent_by(ServerProtocol& prot) override;
    ~GameWorldUpdate();
};

#endif  // !__GAME_WORLD_UPDATE_H__
