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

bool ServerProtocol::send_Worm(const Worm& pt) {
    if (!this->send_short(pt.position.x)) {
        return false;
    }
    if (!this->send_short(pt.position.y)) {
        return false;
    }
    if (!this->send_char(pt.state)) {
        return false;
    }
    if (!this->send_char(pt.id)) {
        return false;
    }
    if (!this->send_char(pt.health_points)) {
        return false;
    }
    if (!this->send_str(pt.map_name)) {
        return false;
    }
    return true;
}

bool ServerProtocol::send_weapon(const WeaponDTO& weapon) {
    if (!this->send_short(weapon.position.x)) {
        return false;
    }
    if (!this->send_short(weapon.position.y)) {
        return false;
    }
    if (!this->send_char(weapon.angle)) {
        return false;
    }
    if (!this->send_char(weapon.id)) {
        return false;
    }
    return true;
}

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

    } else if (code == MSGCODE_PLAYER_MOVE_RIGHT) {
        return BoxMove::move_right(plid);

    } else if (code == MSGCODE_PLAYER_MOVE_LEFT) {
        return BoxMove::move_left(plid);

    } else if (code == MSGCODE_PLAYER_JUMP_FORWARD) {
        return BoxJump::jump_fw(plid);

    } else if (code == MSGCODE_PLAYER_JUMP_BACKWARDS) {
        return BoxJump::jump_bw(plid);

    } else if (code == MSGCODE_SHOOT) {
        uint8_t weapon_id;
        uint16_t power, angle;

        if (!this->cli.recvall(&weapon_id, sizeof(uint8_t), &this->isclosed)) {
            return std::make_shared<NullMessage>();
        }
        if (!this->cli.recvall(&power, sizeof(uint16_t), &this->isclosed)) {
            return std::make_shared<NullMessage>();
        }
        if (!this->cli.recvall(&angle, sizeof(uint16_t), &this->isclosed)) {
            return std::make_shared<NullMessage>();
        }
        return std::make_shared<BoxShoot>(plid, weapon_id, power, angle);

    } else if (code == MSGCODE_CHANGE_WEAPON) {
        uint8_t weapon_id;
        if (!this->cli.recvall(&weapon_id, sizeof(uint8_t), &this->isclosed)) {
            return std::make_shared<NullMessage>();
        }
        return std::make_shared<BoxChangeWeapon>(plid, weapon_id);
        
    } else {
        return std::make_shared<NullMessage>();
    }
    // else if (code == MSGCODE_CHANGE_WEAPON) { // Habria que luego broadcastear el cambio de arma,
    // para que en sdl se actualice
    //     uint8_t weapon_id;
    //     if (!this->cli.recvall(&weapon_id, sizeof(uint8_t), &this->isclosed)) {
    //         return std::make_shared<NullMessage>();
    //     }
    //     return std::make_shared<PlayerChangeWeapon>(plid, weapon_id);
    // }
}

std::unique_ptr<Request> ServerProtocol::recv_request() {
    char code;
    std::cout << "mucho print" << std::endl;
    this->cli.recvall(&code, sizeof(char), &this->isclosed);  // ACA ETO TA MAL >:(
    std::cout << "TODO MAL WACHO" << std::endl;
    if (this->isclosed) {
        return std::make_unique<NullRequest>();
    }
    std::cout << "Received request with code " << (int)code << std::endl;

    if (code == CLI_REQ_GAMES) {
        return std::make_unique<GameDataRequest>();
    } else if (code == CLI_REQ_MAPS) {
        return std::make_unique<MapDataRequest>();
    } else if (code == CLI_REQ_CREATE) {
        std::cout << "Received request to create game" << std::endl;
        std::string game_name;
        std::string map_name;
        if (!this->recv_str(game_name) || !this->recv_str(map_name)) {
            return std::make_unique<NullRequest>();
        }
        std::cout << "Received request to create game " << game_name << " with map " << map_name
                  << std::endl;
        return std::make_unique<CreateRequest>(std::move(game_name), std::move(map_name));
    } else if (code == CLI_REQ_JOIN) {
        std::string game_name;
        if (!this->recv_str(game_name)) {
            return std::make_unique<NullRequest>();
        }
        std::cout << "Received request to join game " << game_name << std::endl;
        return std::make_unique<JoinRequest>(std::move(game_name));
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

char ServerProtocol::send_success() {
    if (!this->send_char(SRV_SUCCESS))
        return CLOSED_SKT;
    return SUCCESS;
}

char ServerProtocol::send_fail() {
    if (!this->send_char(SRV_FAIL))
        return CLOSED_SKT;
    return SUCCESS;
}

bool ServerProtocol::is_connected() { return !this->isclosed; }

void ServerProtocol::close() {
    if (this->isclosed)
        return;

    this->isclosed = true;
    this->cli.shutdown(2);
    this->cli.close();
}
