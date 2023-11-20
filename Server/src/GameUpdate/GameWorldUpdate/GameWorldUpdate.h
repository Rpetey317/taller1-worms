#ifndef __GAME_WORLD_UPDATE_H__
#define __GAME_WORLD_UPDATE_H__

#include <map>
#include <vector>

#include "../GameUpdate.h"

#include "Point.h"

class GameWorldUpdate: public GameUpdate {

    std::map<int, Point> positions;


public:
    explicit GameWorldUpdate(const std::map<int, Point>& positions);

    char get_sent_by(ServerProtocol& prot) override;

    std::map<int, Point>::const_iterator begin() const;
    std::map<int, Point>::const_iterator end() const;

    int get_plcount() const;

    ~GameWorldUpdate();
};

#endif  // !__GAME_WORLD_UPDATE_H__
