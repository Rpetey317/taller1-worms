#include "ServerProtocol.h"

#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "ClientUpdate.h"
#include "GameUpdate.h"


ServerProtocol::ServerProtocol(Socket&& _cli): cli(std::move(_cli)), isclosed(false) {}

char ServerProtocol::send_update(GameUpdate* msg) { return msg->get_sent_by(*this); }

ClientUpdate ServerProtocol::recv_msg() {
    char code;
    ClientUpdate upd;
    this->cli.recvall(&code, sizeof(char), &this->isclosed);
    if (this->isclosed) {
        return upd;
    }

    msglen_t msg_len;
    this->cli.recvall(&msg_len, sizeof(msglen_t), &this->isclosed);
    if (this->isclosed) {
        return upd;
    }
    msg_len = ntohs(msg_len);
    std::vector<char> vmsg(msg_len);
    this->cli.recvall(&vmsg[0], msg_len, &this->isclosed);
    if (this->isclosed) {
        return upd;
    }
    std::string msg(vmsg.begin(), vmsg.end());
    return ClientUpdate(msg);
}

msgcode_t ServerProtocol::recv_request() { 
    msgcode_t request;
    this->cli.recvall(&request, sizeof(msgcode_t), &this->isclosed);
    if (this->isclosed) {
        return -1;
    }
    return request;
}

size_t ServerProtocol::recv_join() { 
    size_t game_code;
    this->cli.recvall(&game_code, sizeof(game_code), &this->isclosed);
    if (this->isclosed) {
        return -1;
    }
    return game_code;
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
