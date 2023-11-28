#include "ChatUpdate.h"

#include "ServerProtocol.h"

ChatUpdate::ChatUpdate(const int& _plid, std::string const& _msg):
        message(_msg), plid(_plid) {}

char ChatUpdate::get_sent_by(ServerProtocol& prot) {
    return prot.send_PlayerMessageUpdate(*this);
}

const std::string& ChatUpdate::get_msg() const { return this->message; }

const int& ChatUpdate::get_plid() const { return this->plid; }

ChatUpdate::~ChatUpdate() = default;
