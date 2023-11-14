#ifndef __GAME_WORLD_UPDATE_H__
#define __GAME_WORLD_UPDATE_H__

#include "../GameUpdate.h"

#include <map>

class GameWorldUpdate : public GameUpdate {

    std::map<int, std::vector<int>> positions;

public:
    GameWorldUpdate();
    ~GameWorldUpdate();
};

#endif // !__GAME_WORLD_UPDATE_H__
