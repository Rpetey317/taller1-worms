#include "GameWorldUpdate.h"

#include "ServerProtocol.h"

#include <iostream>

GameWorldUpdate::GameWorldUpdate(std::map<int, Point>* _positions): positions(_positions) { 
    std::cout << "GameWorldUpdate created" << std::endl; }

char GameWorldUpdate::get_sent_by(ServerProtocol& prot) { return prot.send_WorldUpdate(*this); }

std::map<int, Point>::const_iterator GameWorldUpdate::begin() const {
    return this->positions->begin();
}

std::map<int, Point>::const_iterator GameWorldUpdate::end() const { return this->positions->end(); }

int GameWorldUpdate::get_plcount() const { return this->positions->size(); }

GameWorldUpdate::~GameWorldUpdate() {}
