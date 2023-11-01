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

ClientProtocol::ClientProtocol(Socket skt): skt(std::move(skt)) {}

void ClientProtocol::client_send_msg(const std::string& chat_msg) {
    bool was_closed = false;

    // Send action
    uint8_t action = 5;
    skt.sendall(&action, sizeof(uint8_t), &was_closed);
    if (was_closed) {
        return;
    }

    // Send lenght
    uint16_t lenght = chat_msg.size();
    uint16_t converted_lenght = htons(lenght);
    skt.sendall(&converted_lenght, sizeof(uint16_t), &was_closed);
    if (was_closed) {
        return;
    }

    // Send msg
    skt.sendall(chat_msg.c_str(), lenght, &was_closed);
    if (was_closed) {
        return;
    }
}

std::string ClientProtocol::recv_msg() {
    bool was_closed = false;
    std::string msg = "";
    char action[1];
    this->skt.recvall((int8_t*)action, 1, &was_closed);
    if (was_closed) {
        std::cout << "No hay ningun nuevo mensaje para leer" << std::endl;
        return msg;
    }
    if (action[0] == 9) {  // La accion es Chat
        uint16_t name_size = 0;
        this->skt.recvall(&name_size, sizeof(uint16_t), &was_closed);
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

    } else if (action[0] == 6) {  // La accion es Cantidad de jugadores
        uint8_t amount_players = 0;
        this->skt.recvall(&amount_players, sizeof(uint8_t), &was_closed);
        if (was_closed) {
            std::cout << "Falla lectura de tamanio de palabra" << std::endl;
            return msg;
        }
        msg = create_players_msg((int)amount_players);
    }

    return msg;
}


uint8_t ClientProtocol::receive_gameupdate() {
    bool was_closed = false;
    uint8_t response;
    int sz = this->skt.recvall(&response, sizeof(uint8_t), &was_closed);
    if (sz == 0) {
        throw std::runtime_error("Fallo. No se puede leer retorno de server");
    }

    return response;
}

ClientProtocol::~ClientProtocol() {}
