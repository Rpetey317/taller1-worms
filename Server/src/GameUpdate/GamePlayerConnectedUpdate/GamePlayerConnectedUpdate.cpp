#include "GamePlayerConnectedUpdate.h"

#include "ServerProtocol.h"

GamePlayerConnectedUpdate::PlayerConnectedUpdate(int _player_id): player_id(_player_id) {}

int GamePlayerConnectedUpdate::get_player_id() const { return this->player_id; }

char GamePlayerConnectedUpdate::get_sent_by(ServerProtocol& prot) {
    return prot.send_PlayerConnectedUpdate(*this);
}

GamePlayerConnectedUpdate::~PlayerConnectedUpdate() {}
