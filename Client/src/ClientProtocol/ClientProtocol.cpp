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
        return std::make_shared<NullEvent>(0);
    }
    // Receive players positions
    std::map<int, Worm> worm_positions;

    for (int i = 0; i < amount_players; i++) {
        playerid_t player_id;
        this->skt.recvall(&player_id, sizeof(playerid_t), &this->isclosed);
        if (this->isclosed) {
            return std::make_shared<NullEvent>(0);
        }
        uint16_t x;
        this->skt.recvall(&x, sizeof(uint16_t), &this->isclosed);
        if (this->isclosed) {
            return std::make_shared<NullEvent>(0);
        }
        uint16_t y;
        this->skt.recvall(&y, sizeof(uint16_t), &this->isclosed);
        if (this->isclosed) {
            return std::make_shared<NullEvent>(0);
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
        return std::make_shared<NullEvent>(0);
    }
    uint16_t y;
    this->skt.recvall(&y, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullEvent>(0);
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
        return std::make_shared<NullEvent>(0);
    }
    uint16_t y;
    this->skt.recvall(&y, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullEvent>(0);
    }
    uint8_t angle;
    this->skt.recvall(&angle, sizeof(uint8_t), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullEvent>(0);
    }
    Vect2D position(Vect2D(ntohs(x), ntohs(y)));

    uint8_t exploded;
    this->skt.recvall(&exploded, sizeof(uint8_t), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullEvent>(0);
    }
    if (exploded == 1)
        return std::make_shared<ProyectileUpdate>((int)player_id, type_proyectile, position,
                                                  (int)angle, true);

    return std::make_shared<ProyectileUpdate>((int)player_id, type_proyectile, position, (int)angle,
                                              false);
}

std::shared_ptr<Event> ClientProtocol::recv_timer() {
    playerid_t player_id = this->recv_player_id();
    uint8_t duration;
    this->skt.recvall(&duration, sizeof(uint8_t), &this->isclosed);
    if (this->isclosed) {
        return std::make_shared<NullEvent>(0);
    }
    return std::make_shared<Timer>((int)player_id, (int)duration);
}

ClientProtocol::ClientProtocol(Socket skt): skt(std::move(skt)), isclosed(false) {}

playerid_t ClientProtocol::recv_player_id() {
    playerid_t id;

    this->skt.recvall(&id, sizeof(playerid_t), &this->isclosed);
    if (this->isclosed) {
        return 0;
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
    return SUCCESS;
}

char ClientProtocol::send_Shoot(Shoot action) {
    if (!this->send_char(MSGCODE_SHOOT)) {
        return CLOSED_SKT;
    }

    if (!this->send_char(action.get_weapon())) {
        return CLOSED_SKT;
    }

    if (!this->send_short(action.get_power())) {
        return CLOSED_SKT;
    }

    if (!this->send_short(action.get_angle())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ClientProtocol::send_start() {
    if (!this->send_char(CLI_REQ_START)) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

std::list<std::string> ClientProtocol::req_map_info() { 
    if (!this->send_char(CLI_REQ_MAPS)) {
        return std::list<std::string>();
    }
    uint16_t count;
    this->skt.recvall(&count, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return std::list<std::string>();
    }
    count = ntohs(count);
    std::list<std::string> maps;

    for (int i = 0; i < count; i++) {
        std::string map_name = this->recv_msg();
        if (map_name == "") {
            return maps;
        }
        maps.push_back(map_name);
    }
    return maps;
}

std::list<std::string> ClientProtocol::req_game_info() { 
    if (!this->send_char(CLI_REQ_GAMES)) {
        return std::list<std::string>();
    }
    uint16_t count;
    this->skt.recvall(&count, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return std::list<std::string>();
    }
    count = ntohs(count);
    std::list<std::string> games;

    for (int i = 0; i < count; i++) {
        std::string game_name = this->recv_msg();
        if (game_name == "") {
            return games;
        }
        games.push_back(game_name);
    }
    return games;
}

bool ClientProtocol::req_succeed() { 
    std::cout << "se espera codigo de succes" << std::endl;
    char code;
    this->skt.recvall(&code, sizeof(char), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    std::cout << "se recibe codigo de succes" << std::endl;
    return code == SRV_SUCCESS;
}

char ClientProtocol::create_new_game(std::string& game_name, std::string& map_name) {
    std::cout << "Envio que se cree partida" << std::endl;
    if (!this->send_char(CLI_REQ_CREATE)) {
        return CLOSED_SKT;
    }

    if (!this->send_str(game_name)) {
        return CLOSED_SKT;
    }

    if (!this->send_str(map_name)) {
        return CLOSED_SKT;
    }
    std::cout << "Se crea partida" << std::endl;
    return SUCCESS;
}

char ClientProtocol::join_game(std::string& game_name) {
    if (!this->send_char(CLI_REQ_JOIN)) {
        return CLOSED_SKT;
    }

    if (!this->send_str(game_name)) {
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
        case SRV_TIMER_UPD:
            return this->recv_timer();
        default:
            return std::make_shared<NullEvent>(0);
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


void ClientProtocol::close() {
    if (this->isclosed) {
        return;
    }
    this->skt.shutdown(2);
    this->skt.close();
    this->isclosed = true;
}


ClientProtocol::~ClientProtocol() {}
