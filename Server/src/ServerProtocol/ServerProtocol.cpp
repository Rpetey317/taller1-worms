#include "ServerProtocol.h"

#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "ClientUpdate.h"
#include "GameUpdate.h"
#include "NetworkProtocol.h"

using namespace NetworkProtocol;

bool ServerProtocol::send_short(const uint16_t& num){
    uint16_t nnum = htons(num);
    this->cli.sendall(&nnum, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ServerProtocol::send_long(const uint32_t& num){
    uint32_t nnum = htonl(num);
    this->cli.sendall(&nnum, sizeof(uint32_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ServerProtocol::send_char(const uint8_t& num){
    this->cli.sendall(&num, 1, &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ServerProtocol::send_str(const std::string& str){
    strlen_t len = htonl(str.length());
    this->cli.sendall(&len, sizeof(strlen_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    this->cli.sendall(str.data(), str.length(), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}


ServerProtocol::ServerProtocol(Socket&& _cli): cli(std::move(_cli)), isclosed(false) {}

char ServerProtocol::send_update(GameUpdate* msg) { return msg->get_sent_by(*this); }

ClientUpdate ServerProtocol::recv_msg() {
    char code;
    ClientUpdate upd;
    this->cli.recvall(&code, sizeof(char), &this->isclosed);
    if (this->isclosed) {
        return upd;
    }

    strlen_t msg_len;
    this->cli.recvall(&msg_len, sizeof(strlen_t), &this->isclosed);
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

char ServerProtocol::send_PlayerMessageUpdate(const PlayerMessageUpdate& upd) {
    // send code
    if (!this->send_char(MSGCODE_PLAYER_MESSAGE)) {
        return CLOSED_SKT;
    }

    // send message
    if (!this->send_str(upd.get_msg())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ServerProtocol::send_TurnChangeUpdate(const TurnChangeUpdate& upd){
    // send code
    if (!this->send_char(MSGCODE_TURN_UPDATE)) {
        return CLOSED_SKT;
    }

    // send new current player id
    if (!this->send_long(upd.get_new_curr_player())) {
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
