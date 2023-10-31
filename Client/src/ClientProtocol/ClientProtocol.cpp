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

void ClientProtocol::client_send_msg(std::vector<std::variant<uint8_t, uint16_t>> parsed_command) {
    bool was_closed = false;
    for (const auto& value: parsed_command) {
        if (std::holds_alternative<uint8_t>(value)) {
            uint8_t byte_value = std::get<uint8_t>(value);
            int sz = skt.sendall(&byte_value, sizeof(uint8_t), &was_closed);
            if (sz == 0) {
                return;
            }
        } else if (std::holds_alternative<uint16_t>(value)) {
            uint16_t two_byte_value = std::get<uint16_t>(value);
            int sz = skt.sendall(&two_byte_value, sizeof(uint16_t), &was_closed);
            if (sz == 0) {
                return;
            }
        }
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
