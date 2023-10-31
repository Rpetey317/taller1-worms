#include "ServerProtocol.h"

#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "ClientUpdate.h"
#include "GameUpdate.h"
#include "NetworkProtocol.h"

using NetworkProtocol::msgcode_t;
using NetworkProtocol::msglen_t;

using NetworkProtocol::MSGCODE_PLAYER_CONNECT;
using NetworkProtocol::MSGCODE_PLAYER_DISCONNECT;
using NetworkProtocol::MSGCODE_PLAYER_MESSAGE;

ServerProtocol::ServerProtocol(Socket&& _cli): cli(std::move(_cli)), isclosed(false) {}

char ServerProtocol::send_update(GameUpdate* msg) { return msg->get_sent_by(*this); }

ClientUpdate ServerProtocol::recv_msg() {
    char code;
    this->cli.recvall(&code, sizeof(char), &this->isclosed);
    if (this->isclosed) {
        return ClientUpdate(NO_MSG_RECV);
    }

    msglen_t msg_len;
    this->cli.recvall(&msg_len, sizeof(msglen_t), &this->isclosed);
    if (this->isclosed) {
        return ClientUpdate(NO_MSG_RECV);
    }
    msg_len = ntohs(msg_len);
    std::vector<char> vmsg(msg_len);
    this->cli.recvall(&vmsg[0], msg_len, &this->isclosed);
    if (this->isclosed) {
        return ClientUpdate(NO_MSG_RECV);
    }
    std::string msg(vmsg.begin(), vmsg.end());
    return ClientUpdate(msg);
}

char ServerProtocol::send_PlayerMessageUpdate(const PlayerMessageUpdate& upd) {
    // send code
    msgcode_t code = MSGCODE_PLAYER_MESSAGE;
    this->cli.sendall(&code, sizeof(msgcode_t), &this->isclosed);
    if (this->isclosed) {
        return CLOSED_SKT;
    }

    // send message length
    msglen_t msg_len = htons(upd.get_msg().length());
    this->cli.sendall(&msg_len, sizeof(msglen_t), &this->isclosed);
    if (this->isclosed) {
        return CLOSED_SKT;
    }

    // send message
    this->cli.sendall(upd.get_msg().data(), upd.get_msg().length(), &this->isclosed);
    if (this->isclosed) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

bool ServerProtocol::is_connected() { return !this->isclosed; }

void ServerProtocol::close() {
    if (this->isclosed)
        return;

    this->cli.shutdown(2);
    this->cli.close();
    this->isclosed = true;
}