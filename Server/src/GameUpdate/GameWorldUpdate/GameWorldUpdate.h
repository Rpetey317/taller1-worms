#ifndef __GAME_WORLD_UPDATE_H__
#define __GAME_WORLD_UPDATE_H__

#include <map>
#include <vector>

#include "../GameUpdate.h"

class GameWorldUpdate: public GameUpdate {

    std::map<int, std::vector<int>> positions;

public:
    GameWorldUpdate(const std::map<int, std::vector<int>>& positions);
    ~GameWorldUpdate();
};

#endif  // !__GAME_WORLD_UPDATE_H__
