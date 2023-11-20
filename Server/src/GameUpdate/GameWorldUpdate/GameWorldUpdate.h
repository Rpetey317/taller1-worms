#ifndef __GAME_WORLD_UPDATE_H__
#define __GAME_WORLD_UPDATE_H__

#include <map>
#include <vector>

#include "../GameUpdate.h"

class GameWorldUpdate: public GameUpdate {

    std::map<int, std::vector<int>> positions;

public:
    explicit GameWorldUpdate(const std::map<int, std::vector<int>>& positions);
    char get_sent_by(ServerProtocol& prot) override;
    ~GameWorldUpdate();
};

#endif  // !__GAME_WORLD_UPDATE_H__
