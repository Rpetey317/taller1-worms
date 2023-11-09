#include "GamePlayerDisconnectedUpdate.h"

#include "ServerProtocol.h"

GamePlayerDisconnectedUpdate::PlayerDisconnectedUpdate(int _player_id): player_id(_player_id) {}

int GamePlayerDisconnectedUpdate::get_player_id() const { return this->player_id; }

char GamePlayerDisconnectedUpdate::get_sent_by(ServerProtocol& prot) {
    return prot.send_PlayerDisconnectedUpdate(*this);
}

GamePlayerDisconnectedUpdate::~PlayerDisconnectedUpdate() {}
