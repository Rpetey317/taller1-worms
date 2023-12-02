#include "WorldUpdate.h"

#include <iostream>

#include "ServerProtocol.h"

WorldUpdate::WorldUpdate(std::map<int, Vect2D>* _positions): positions(_positions) {}

char WorldUpdate::get_sent_by(ServerProtocol& prot) { return prot.send_WorldUpdate(*this); }

std::map<int, Vect2D>::const_iterator WorldUpdate::begin() const {
    return this->positions->begin();
}

std::map<int, Vect2D>::const_iterator WorldUpdate::end() const { return this->positions->end(); }

int WorldUpdate::get_plcount() const { return this->positions->size(); }

WorldUpdate::~WorldUpdate() {}
