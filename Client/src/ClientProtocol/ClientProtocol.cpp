#include "ClientProtocol.h"


#include <iostream>
#include <sstream>

#include <arpa/inet.h>


std::string ClientProtocol::create_players_msg(int amount_players) {
    std::string amount_players_str = std::to_string(amount_players);
    std::string amount_players_msg =
            "Jugadores " + amount_players_str + ", esperando al resto de tus amigos...";
    return amount_players_msg;
}

ClientProtocol::ClientProtocol(Socket skt): skt(std::move(skt)), was_closed(false) {}

void ClientProtocol::send_msg(const std::string& chat_msg) {
    // Send lenght
    msglen_t msg_lenght = htons(chat_msg.size());
    skt.sendall(&msg_lenght, sizeof(msglen_t), &this->was_closed);
    if (this->was_closed) {
        return;
    }

    // Send msg
    skt.sendall(chat_msg.c_str(), ntohs(msg_lenght), &this->was_closed);
    if (this->was_closed) {
        return;
    }
}

void ClientProtocol::send_code(msgcode_t action) {
    // Send action
    skt.sendall(&action, sizeof(msgcode_t), &this->was_closed);
    if (this->was_closed) {
        return;
    }
}

void ClientProtocol::send_code_game(size_t code) {
    // Send code game to join
    skt.sendall(&code, sizeof(msgcode_t), &this->was_closed);
    if (this->was_closed) {
        return;
    }
}

msgcode_t ClientProtocol::recv_code() {
    msgcode_t code;
    skt.recvall(&code, 1, &this->was_closed);
    if (this->was_closed) {
        return ERROR;
    }
    return code;
}

std::string ClientProtocol::recv_msg() {
    std::string msg = "";
    msglen_t name_size;
    this->skt.recvall(&name_size, sizeof(msglen_t), &was_closed);
    if (was_closed) {
        std::cout << "Falla lectura de tamanio de palabra" << std::endl;
        return msg;
    }
    name_size = ntohs(name_size);
    std::vector<char> vname(name_size);
    this->skt.recvall(&vname[0], name_size, &was_closed);
    if (was_closed) {
        return msg;
    }
    std::string chatmsg(vname.begin(), vname.end());
    msg = chatmsg;
    return msg;
}

int ClientProtocol::recv_amount_players() {
    amount_players_t playercount;
    skt.recvall(&playercount, sizeof(amount_players_t), &this->was_closed);
    if (this->was_closed) {
        return ERROR;
    }
    return (int)playercount;
}


// uint8_t ClientProtocol::receive_gameupdate() {
//     bool was_closed = false;
//     uint8_t response;
//     int sz = this->skt.recvall(&response, sizeof(uint8_t), &was_closed);
//     if (sz == 0) {
//         throw std::runtime_error("Fallo. No se puede leer retorno de server");
//     }

//     return response;
// }

void ClientProtocol::close() {
    if (this->was_closed)
        return;

    this->skt.shutdown(2);
    this->skt.close();
    this->was_closed = true;
}


ClientProtocol::~ClientProtocol() {}
