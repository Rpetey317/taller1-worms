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

ServerProtocol::ServerProtocol(Socket&& _cli): cli(std::move(_cli)), isclosed(false) {}

ServerProtocol::ServerProtocol(ServerProtocol&& other):
        cli(std::move(other.cli)), isclosed(other.isclosed) {}

// DD methods for each update type implemented in ServerProtocol_sendUpdate.cpp
char ServerProtocol::send_update(std::shared_ptr<Update> msg) { return msg->get_sent_by(*this); }

std::shared_ptr<Message> ServerProtocol::recv_update(const int& plid) {
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
    } else {
        return std::make_shared<NullMessage>();
    }
}

std::unique_ptr<Request> ServerProtocol::recv_request() {
    char code;
    this->cli.recvall(&code, sizeof(char), &this->isclosed);
    if (this->isclosed) {
        return std::make_unique<NullRequest>();
    }

    if (code == CLI_REQ_GAMES) {
        return std::make_unique<GameDataRequest>();
    } else if (code == CLI_REQ_MAPS) {
        return std::make_unique<MapDataRequest>();
    } else {
        return std::make_unique<NullRequest>();
    }
}

bool ServerProtocol::recv_game_start() {
    char code;
    this->cli.recvall(&code, sizeof(char), &this->isclosed);
    if (this->isclosed) {
        return false;
    }

    if (code == CLI_REQ_START)
        return true;
    return false;
}

char ServerProtocol::send_game_data(const std::list<std::string>& names) {
    if (!this->send_char(SRV_RESP_GAMES))
        return CLOSED_SKT;

    if (!this->send_short(names.size()))
        return CLOSED_SKT;

    for (auto& name: names) {
        // cppcheck-suppress useStlAlgorithm
        if (!this->send_str(name))
            return CLOSED_SKT;
    }
    return SUCCESS;
}

char ServerProtocol::send_map_data(const std::list<std::string>& names) {
    if (!this->send_char(SRV_RESP_MAPS))
        return CLOSED_SKT;

    if (!this->send_short(names.size()))
        return CLOSED_SKT;

    for (auto& name: names) {
        // cppcheck-suppress useStlAlgorithm
        if (!this->send_str(name)) {
            return CLOSED_SKT;
        }
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
