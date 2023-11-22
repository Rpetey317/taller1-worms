#include "GameWorldUpdate.h"

#include <iostream>

#include "ServerProtocol.h"

GameWorldUpdate::GameWorldUpdate(std::map<int, Vect2D>* _positions): positions(_positions) {}

char GameWorldUpdate::get_sent_by(ServerProtocol& prot) { return prot.send_WorldUpdate(*this); }

std::map<int, Vect2D>::const_iterator GameWorldUpdate::begin() const {
    return this->positions->begin();
}

std::map<int, Vect2D>::const_iterator GameWorldUpdate::end() const {
    return this->positions->end();
}

int GameWorldUpdate::get_plcount() const { return this->positions->size(); }

GameWorldUpdate::~GameWorldUpdate() {}
