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

void ClientProtocol::client_send_msg(const std::string &chat_msg) {
    bool was_closed = false;
    
    //Send action
    uint8_t action = 5;
    int sz = skt.sendall(&action, sizeof(uint8_t), &was_closed);
    if (sz == 0) {
        return;
    }

    //Send lenght
    uint16_t lenght = chat_msg.size();
    uint16_t converted_lenght = htons(lenght);
    sz = skt.sendall(&converted_lenght, sizeof(uint16_t), &was_closed);
    if (sz == 0) {
        return;
    }

    //Send msg
    sz = skt.sendall(chat_msg.c_str(), lenght, &was_closed);
    if (sz == 0) {
        return;
    }
}

std::string ClientProtocol::recv_msg() {
    bool was_closed = false;
    std::string msg = "";
    char action[1];
    int sz = this->skt.recvall((int8_t*)action, 1, &was_closed);
    if (sz == 0) {
        std::cout << "No hay ningun nuevo mensaje para leer" << std::endl;
        return msg;
    }
    if (action[0] == 9) {  // La accion es Chat
        char letter[1];
        uint16_t name_size = 0;
        sz = this->skt.recvall(&name_size, sizeof(uint16_t), &was_closed);
        if (sz == 0) {
            std::cout << "Falla lectura de tamanio de palabra" << std::endl;
            return msg;
        }
        name_size = ntohs(name_size);
        size_t converted_size = static_cast<size_t>(name_size);
        for (size_t i = 0; i < converted_size; i++) {
            sz = this->skt.recvall(letter, 1, &was_closed);
            if (sz == 0) {
                std::cout << "Falla lectura de letra palabra" << std::endl;
                return msg;
            }
            msg.append(letter);
        }
    } else if (action[0] == 6) {  // La accion es Cantidad de jugadores
        uint8_t amount_players = 0;
        sz = this->skt.recvall(&amount_players, sizeof(uint8_t), &was_closed);
        if (sz == 0) {
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
