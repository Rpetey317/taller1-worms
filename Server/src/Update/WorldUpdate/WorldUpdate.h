#ifndef __GAME_WORLD_UPDATE_H__
#define __GAME_WORLD_UPDATE_H__

#include <map>
#include <vector>

#include "../Update.h"

#include "Vect2D.h"
#include "WeaponDTO.h"
#include "Worm.h"

class WorldUpdate: public Update {

    std::map<int, Worm>* positions;
    std::map<int, WeaponDTO>* weapons;


public:
    explicit WorldUpdate(std::map<int, Worm>* positions);
    WorldUpdate(std::map<int, Worm>* positions, std::map<int, WeaponDTO>* weapons);

    char get_sent_by(ServerProtocol& prot) override;

    std::map<int, Worm>::const_iterator begin() const;
    std::map<int, Worm>::const_iterator end() const;

    std::map<int, WeaponDTO>::const_iterator begin_weapons() const;
    std::map<int, WeaponDTO>::const_iterator end_weapons() const;


    int get_plcount() const;
    int get_weaponscount() const;

    ~WorldUpdate();
};

#endif  // !__GAME_WORLD_UPDATE_H__
