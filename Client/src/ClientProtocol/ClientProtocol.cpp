#include "ClientProtocol.h"

#include <iostream>
#include <map>
#include <sstream>

#include <arpa/inet.h>


bool ClientProtocol::send_short(const uint16_t& num) {
    uint16_t nnum = htons(num);
    this->skt.sendall(&nnum, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ClientProtocol::send_long(const uint32_t& num) {
    uint32_t nnum = htonl(num);
    this->skt.sendall(&nnum, sizeof(uint32_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ClientProtocol::send_char(const uint8_t& num) {
    this->skt.sendall(&num, 1, &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ClientProtocol::send_str(const std::string& str) {
    strlen_t len = htons(str.length());
    this->skt.sendall(&len, sizeof(strlen_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    this->skt.sendall(str.data(), str.length(), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

std::string ClientProtocol::recv_msg() {
    std::string msg = "";
    strlen_t name_size;
    this->skt.recvall(&name_size, sizeof(strlen_t), &isclosed);
    if (this->isclosed) {
        std::cout << "Falla lectura de tamanio de palabra" << std::endl;
        return msg;
    }
    name_size = ntohs(name_size);
    std::vector<char> vname(name_size);
    this->skt.recvall(&vname[0], name_size, &isclosed);
    if (isclosed) {
        return msg;
    }
    std::string chatmsg(vname.begin(), vname.end());
    msg = chatmsg;
    return msg;
}

std::shared_ptr<Event> ClientProtocol::recv_player_connected() {
    playerid_t player_id = this->recv_player_id();
    return std::make_shared<PlayerConnected>((int)player_id);
}

std::shared_ptr<Event> ClientProtocol::recv_player_message() {
    playerid_t player_id = this->recv_player_id();
    std::string msg = this->recv_msg();
    if (msg == "") {
        return std::make_shared<NullEvent>(player_id);
    }
    return std::make_shared<PlayerMessage>((int)player_id, msg);
}

std::shared_ptr<Event> ClientProtocol::recv_player_disconnected() {
    playerid_t player_id = this->recv_player_id();
    return std::make_shared<PlayerDisconnected>((int)player_id);
}

std::shared_ptr<Event> ClientProtocol::recv_turn_update() {
    playerid_t player_id = this->recv_player_id();
    return std::make_shared<TurnUpdate>((int)player_id);
}

std::shared_ptr<Event> ClientProtocol::recv_map_update() {

    // Receive amount players or map size
    amount_players_t amount_players;
    this->skt.recvall(&amount_players, sizeof(amount_players_t), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullEvent>(-1);
    }
    // Receive players positions
    std::map<int, Worm> worm_positions;

    for (int i = 0; i < amount_players; i++) {
        playerid_t player_id;
        this->skt.recvall(&player_id, sizeof(playerid_t), &this->isclosed);
        if (this->isclosed) {
            return std::make_shared<NullEvent>(-1);
        }
        uint16_t x;
        this->skt.recvall(&x, sizeof(uint16_t), &this->isclosed);
        if (this->isclosed) {
            return std::make_shared<NullEvent>(-1);
        }
        uint16_t y;
        this->skt.recvall(&y, sizeof(uint16_t), &this->isclosed);
        if (this->isclosed) {
            return std::make_shared<NullEvent>(-1);
        }
        Vect2D position(Vect2D(ntohs(x), ntohs(y)));
        Worm worm(position, (int)player_id);
        worm_positions[(int)player_id] = worm;
    }
    return std::make_shared<MapUpdate>(worm_positions);
}

std::shared_ptr<Event> ClientProtocol::recv_player_position() {
    playerid_t player_id = this->recv_player_id();
    uint16_t x;
    this->skt.recvall(&x, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullEvent>(-1);
    }
    uint16_t y;
    this->skt.recvall(&y, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullEvent>(-1);
    }
    Vect2D position(Vect2D(ntohs(x), ntohs(y)));
    return std::make_shared<PlayerPosition>((int)player_id, position);
}

std::shared_ptr<Event> ClientProtocol::recv_proyectile_update() {
    playerid_t player_id = this->recv_player_id();
    std::string type_proyectile = this->recv_msg();
    uint16_t x;
    this->skt.recvall(&x, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullEvent>(-1);
    }
    uint16_t y;
    this->skt.recvall(&y, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullEvent>(-1);
    }
    uint8_t angle;
    this->skt.recvall(&angle, sizeof(uint8_t), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullEvent>(-1);
    }
    Vect2D position(Vect2D(ntohs(x), ntohs(y)));

    uint8_t exploded;
    this->skt.recvall(&exploded, sizeof(uint8_t), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullEvent>(-1);
    }
    if (exploded == 1)
        return std::make_shared<ProyectileUpdate>((int)player_id, type_proyectile, position,
                                                  (int)angle, true);

    return std::make_shared<ProyectileUpdate>((int)player_id, type_proyectile, position, (int)angle,
                                              false);
}

ClientProtocol::ClientProtocol(Socket skt): skt(std::move(skt)), isclosed(false) {}

playerid_t ClientProtocol::recv_player_id() {
    playerid_t id;

    this->skt.recvall(&id, sizeof(playerid_t), &this->isclosed);
    if (this->isclosed) {
        return -1;
    }
    return id;
}

char ClientProtocol::send_Message(Message action) {
    // Send code

    if (!this->send_char(MSGCODE_PLAYER_MESSAGE))
        return CLOSED_SKT;

    // Send msg
    if (!this->send_str(action.get_msg()))
        return CLOSED_SKT;

    return SUCCESS;
}

char ClientProtocol::send_Movement(Move action) {
    // Send code
    if (action.is_right()) {
        if (!this->send_char(MSGCODE_PLAYER_MOVE_RIGHT)) {
            return CLOSED_SKT;
        }
    } else {
        if (!this->send_char(MSGCODE_PLAYER_MOVE_LEFT)) {
            return CLOSED_SKT;
        }
    }
    return SUCCESS;
}

char ClientProtocol::send_Jump(Jump action) {
    // Send code
    if (action.is_forward()) {
        if (!this->send_char(MSGCODE_PLAYER_JUMP_FORWARD))
            return CLOSED_SKT;
    } else {
        if (!this->send_char(MSGCODE_PLAYER_JUMP_BACKWARDS))
            return CLOSED_SKT;
    }
    return SUCCESS;
}

char ClientProtocol::send_NullAction(NullAction action) {
    if (!this->send_char(MSGCODE_NULL_ACTION)) {
        return CLOSED_SKT;
    }
    return SUCCESS;
}

char ClientProtocol::send_Shoot(Shoot action) {
    if (!this->send_char(MSGCODE_SHOOT)) {
        return CLOSED_SKT;
    }

    if (!this->send_char(action.get_weapon())) {
        return CLOSED_SKT;
    }

    if (!this->send_char(action.get_power())) {
        return CLOSED_SKT;
    }

    if (!this->send_char(action.get_angle())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}


void ClientProtocol::send_code_game(size_t code) {
    // Send code game to join
    skt.sendall(&code, sizeof(msgcode_t), &this->isclosed);
    if (this->isclosed) {
        return;
    }
}

std::shared_ptr<Event> ClientProtocol::recv_update() {
    // TODO: change this to a dynamic switch
    msgcode_t code_update = this->recv_code();
    if (code_update == MSGCODE_WORLD_UPD) {
        return this->recv_map_update();
    }
    switch (code_update) {
        case MSGCODE_ACK:
            return this->recv_player_connected();
        case MSGCODE_PLAYER_CONNECT:
            return this->recv_player_connected();
        case MSGCODE_PLAYER_MESSAGE:
            return this->recv_player_message();
        case MSGCODE_PLAYER_DISCONNECT:
            return this->recv_player_disconnected();
        case MSGCODE_TURN_UPDATE:
            return this->recv_turn_update();
        case MSGCODE_PLAYER_POSITION:
            return this->recv_player_position();
        case MSGCODE_PROYECTILE_UPDATE:
            return this->recv_proyectile_update();
        default:
            return std::make_shared<NullEvent>(-1);
    }
}

msgcode_t ClientProtocol::recv_code() {
    msgcode_t code;
    skt.recvall(&code, 1, &this->isclosed);
    if (this->isclosed) {
        return ERROR;
    }
    return code;
}


int ClientProtocol::recv_amount_players() {
    amount_players_t playercount;
    skt.recvall(&playercount, sizeof(amount_players_t), &this->isclosed);
    if (this->isclosed) {
        return ERROR;
    }
    return (int)playercount;
}


// uint8_t ClientProtocol::receive_gameupdate() {
//     bool isclosed = false;
//     uint8_t response;
//     int sz = this->skt.recvall(&response, sizeof(uint8_t), &isclosed);
//     if (sz == 0) {
//         throw std::runtime_error("Fallo. No se puede leer retorno de server");
//     }

//     return response;
// }

void ClientProtocol::close() {
    if (this->isclosed) {
        return;
    }
    this->skt.shutdown(2);
    this->skt.close();
    this->isclosed = true;
}


ClientProtocol::~ClientProtocol() {}
