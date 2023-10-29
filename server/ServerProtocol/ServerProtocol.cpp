#include "ServerProtocol.h"

#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "common/NetworkProtocol.h"
#include "server/ClientUpdate/ClientUpdate.h"
#include "server/GameUpdate/GameUpdate.h"

using NetworkProtocol::msglen_t;

ServerProtocol::ServerProtocol(Socket&& _cli): cli(std::move(_cli)), isclosed(false) {}

void ServerProtocol::send_msg(const GameUpdate& _msg) {
    if (this->isclosed) {
        return;
    }

    char wr_buffer = 0;
    std::string msg = _msg.get_msg();

    // Send code
    this->cli.sendall(&wr_buffer, 1, &this->isclosed);
    if (isclosed) {
        this->isclosed = true;
        return;
    }

    // Send message length
    msglen_t name_size = htons(msg.length());
    this->cli.sendall(&name_size, sizeof(msglen_t), &this->isclosed);
    if (isclosed) {
        this->isclosed = true;
        return;
    }

    // Send message
    this->cli.sendall(msg.data(), ntohs(name_size), &this->isclosed);
    if (isclosed) {
        this->isclosed = true;
        return;
    }

    return;
}

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

bool ServerProtocol::is_connected() { return !this->isclosed; }

void ServerProtocol::close() {
    if (this->isclosed)
        return;

    this->cli.shutdown(2);
    this->cli.close();
    this->isclosed = true;
}
