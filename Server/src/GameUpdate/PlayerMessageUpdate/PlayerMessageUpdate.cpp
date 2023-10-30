#include "PlayerMessageUpdate.h"


PlayerMessageUpdate::PlayerMessageUpdate(std::string const& _msg): message(_msg) {}

char PlayerMessageUpdate::get_sent_by(ServerProtocol& prot) const {
    return prot.send_PlayerMessageUpdate(*this);    
}

const std::string& PlayerMessageUpdate::get_msg() const{
    return this->message;
}

