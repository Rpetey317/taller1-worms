#ifndef __GAME_WORLD_UPDATE_H__
#define __GAME_WORLD_UPDATE_H__

#include <map>
#include <vector>

#include "../Update.h"

#include "Vect2D.h"

class WorldUpdate: public Update {

    std::map<int, Vect2D>* positions;


public:
    explicit WorldUpdate(std::map<int, Vect2D>* positions);

    char get_sent_by(ServerProtocol& prot) override;

    std::map<int, Vect2D>::const_iterator begin() const;
    std::map<int, Vect2D>::const_iterator end() const;

    int get_plcount() const;

    ~WorldUpdate();
};

#endif  // !__GAME_WORLD_UPDATE_H__
