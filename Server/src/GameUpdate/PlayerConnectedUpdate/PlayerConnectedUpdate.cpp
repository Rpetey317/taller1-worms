#include "PlayerConnectedUpdate.h"

#include "ServerProtocol.h"

PlayerConnectedUpdate::PlayerConnectedUpdate(int _player_id): player_id(_player_id) {}

int PlayerConnectedUpdate::get_player_id() const { return this->player_id; }

char PlayerConnectedUpdate::get_sent_by(ServerProtocol& prot) {
    return prot.send_PlayerConnectedUpdate(*this);
}

PlayerConnectedUpdate::~PlayerConnectedUpdate() {}
