#include "PlayerMessageUpdate.h"

#include "ServerProtocol.h"

PlayerMessageUpdate::PlayerMessageUpdate(const int& _plid, std::string const& _msg):
        message(_msg), plid(_plid) {}

char PlayerMessageUpdate::get_sent_by(ServerProtocol& prot) {
    return prot.send_PlayerMessageUpdate(*this);
}

const std::string& PlayerMessageUpdate::get_msg() const { return this->message; }

const int& PlayerMessageUpdate::get_plid() const { return this->plid; }
