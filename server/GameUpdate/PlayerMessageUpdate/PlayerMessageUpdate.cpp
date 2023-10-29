#include "PlayerMessageUpdate.h"

#include <arpa/inet.h>

#include "common/NetworkProtocol.h"

using NetworkProtocol::MSGCODE_PLAYER_MESSAGE;
using NetworkProtocol::msglen_t;

PlayerMessageUpdate::PlayerMessageUpdate(std::string const& _msg): message(_msg) {}

char PlayerMessageUpdate::get_code() const { return MSGCODE_PLAYER_MESSAGE; }

std::vector<char> PlayerMessageUpdate::get_serialized_msg() const {
    std::vector<char> msg;

    msglen_t msg_len = htons(this->message.length());
    char* ln_as_char = (char*)&msg_len;

    for (int i = 0; i < sizeof(msglen_t); i++) {
        msg.push_back(ln_as_char[i]);
    }

    for (auto it = this->message.begin(); it != this->message.end(); ++it) {
        msg.push_back(*it);
    }
    return msg;
}
