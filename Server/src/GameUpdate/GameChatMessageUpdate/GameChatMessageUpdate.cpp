#include "GameChatMessageUpdate.h"

#include "ServerProtocol.h"

GameChatMessageUpdate::GameChatMessageUpdate(const int& _plid, std::string const& _msg):
        message(_msg), plid(_plid) {}

char GameChatMessageUpdate::get_sent_by(ServerProtocol& prot) {
    return prot.send_PlayerMessageUpdate(*this);
}

const std::string& GameChatMessageUpdate::get_msg() const { return this->message; }

const int& GameChatMessageUpdate::get_plid() const { return this->plid; }

GameChatMessageUpdate::~GameChatMessageUpdate() = default;
