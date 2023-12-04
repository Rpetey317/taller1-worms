#ifndef __GAME_WORLD_UPDATE_H__
#define __GAME_WORLD_UPDATE_H__

#include <map>
#include <vector>

#include "../Update.h"

#include "Vect2D.h"
#include "Worm.h"

class WorldUpdate: public Update {

    std::map<int, Worm>* positions;


public:
    explicit WorldUpdate(std::map<int, Worm>* positions);

    char get_sent_by(ServerProtocol& prot) override;

    std::map<int, Worm>::const_iterator begin() const;
    std::map<int, Worm>::const_iterator end() const;

    int get_plcount() const;

    ~WorldUpdate();
};

#endif  // !__GAME_WORLD_UPDATE_H__
