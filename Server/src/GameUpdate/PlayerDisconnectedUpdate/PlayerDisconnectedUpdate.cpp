#include "PlayerDisconnectedUpdate.h"
#include "ServerProtocol.h"

PlayerDisconnectedUpdate::PlayerDisconnectedUpdate(int _player_id):
        player_id(_player_id) {}

int PlayerDisconnectedUpdate::get_player_id() const { return this->player_id; } 

char PlayerDisconnectedUpdate::get_sent_by(ServerProtocol& prot) { 
    return prot.send_PlayerDisconnectedUpdate(*this); 
    } 

PlayerDisconnectedUpdate::~PlayerDisconnectedUpdate() {}    
