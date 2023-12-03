#include "ServerProtocol.h"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "Update.h"

// I thoroughly refuse to manually write the using directive
// for every. single. constant. in the NetworkProtocol namespace.
using namespace NetworkProtocol;  // NOLINT

bool ServerProtocol::send_short(const uint16_t& num) {
    uint16_t nnum = htons(num);
    this->cli.sendall(&nnum, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ServerProtocol::send_long(const uint32_t& num) {
    uint32_t nnum = htonl(num);
    this->cli.sendall(&nnum, sizeof(uint32_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ServerProtocol::send_char(const uint8_t& num) {
    this->cli.sendall(&num, 1, &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ServerProtocol::send_str(const std::string& str) {
    strlen_t len = htons(str.length());
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

bool ServerProtocol::send_Vect2D(const Vect2D& pt) {
    if (!this->send_short(pt.x)) {
        return false;
    }
    if (!this->send_short(pt.y)) {
        return false;
    }
    return true;
}


ServerProtocol::ServerProtocol(Socket&& _cli, const int& _plid):
        cli(std::move(_cli)), isclosed(false), plid(_plid) {}

// DD methods for each update type implemented in ServerProtocol_sendUpdate.cpp
char ServerProtocol::send_update(std::shared_ptr<Update> msg) { return msg->get_sent_by(*this); }

std::shared_ptr<Message> ServerProtocol::recv_update() {
    char code;
    this->cli.recvall(&code, sizeof(char), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullMessage>();
    }

    // TODO: fix this
    if (code == MSGCODE_PLAYER_MESSAGE) {

        strlen_t msg_len;
        this->cli.recvall(&msg_len, sizeof(strlen_t), &this->isclosed);
        if (this->isclosed) {
            return std::make_shared<NullMessage>();
        }

        msg_len = ntohs(msg_len);
        std::vector<char> vmsg(msg_len);
        this->cli.recvall(&vmsg[0], msg_len, &this->isclosed);
        if (this->isclosed) {
            return std::make_shared<NullMessage>();
        }
        std::string msg(vmsg.begin(), vmsg.end());
        return std::make_shared<Chat>(plid, msg);
    } else if (code == MSGCODE_BOX2D) {
        input_t input;
        this->cli.recvall(&input, sizeof(input_t), &this->isclosed);
        if (this->isclosed) {
            return std::make_shared<NullMessage>();
        }
        return std::make_shared<Box2DMsg>(plid, input);
    } else if (code == MSGCODE_PLAYER_MOVE_RIGHT) {
        return std::make_shared<Box2DMsg>(plid, 1);
    } else if (code == MSGCODE_PLAYER_MOVE_LEFT) {
        return std::make_shared<Box2DMsg>(plid, 2);
    } else if (code == MSGCODE_PLAYER_JUMP_FORWARD) {

    } else if (code == MSGCODE_PLAYER_JUMP_BACKWARDS) {

    } else if (code == MSGCODE_PLAYER_MOVE_LEFT) {

    } else if (code == MSGCODE_PLAYER_MOVE_RIGHT) {

    } else if (code == MSGCODE_SHOOT) {

    } else {
        return std::make_shared<NullMessage>();
    }
    return std::make_shared<NullMessage>();  // del this
}

msgcode_t ServerProtocol::recv_request() {
    msgcode_t request;
    this->cli.recvall(&request, sizeof(msgcode_t), &this->isclosed);
    if (this->isclosed) {
        return -1;
    }
    return request;
}

bool ServerProtocol::is_connected() { return !this->isclosed; }

void ServerProtocol::close() {
    if (this->isclosed)
        return;

    this->isclosed = true;
    this->cli.shutdown(2);
    this->cli.close();
}
