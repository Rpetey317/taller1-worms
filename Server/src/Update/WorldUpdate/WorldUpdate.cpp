#include "WorldUpdate.h"

#include <iostream>

#include "ServerProtocol.h"

WorldUpdate::WorldUpdate(std::map<int, Worm>* _positions): positions(_positions) {}

WorldUpdate::WorldUpdate(std::map<int, Worm>* positions, std::map<int, WeaponDTO>* weapons):
        positions(positions), weapons(weapons) {}

char WorldUpdate::get_sent_by(ServerProtocol& prot) { return prot.send_WorldUpdate(*this); }

std::map<int, Worm>::const_iterator WorldUpdate::begin() const { return this->positions->begin(); }

std::map<int, WeaponDTO>::const_iterator WorldUpdate::begin_weapons() const {
    return this->weapons->begin();
}

std::map<int, WeaponDTO>::const_iterator WorldUpdate::end_weapons() const {
    return this->weapons->end();
}


std::map<int, Worm>::const_iterator WorldUpdate::end() const { return this->positions->end(); }

int WorldUpdate::get_plcount() const { return this->positions->size(); }

int WorldUpdate::get_weaponscount() const { return this->weapons->size(); }

WorldUpdate::~WorldUpdate() {}
