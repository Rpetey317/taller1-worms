#include "Client.h"

#include <iostream>
#include <sstream>

Client::Client(const char* hostname, const char* port):
        parser(), protocol(Socket(hostname, port)) {}

std::string Client::ask_for_command() {
    std::string command;
    std::getline(std::cin, command);
    std::istringstream s(command);
    std::string action;
    s >> action;
    while (action != "Chat" && action != "Read" && action != "Exit") {
        std::cout << "Ingrese un comando posible" << std::endl;
        std::getline(std::cin, command);
        std::istringstream s_new(command);
        s_new >> action;
    }
    return command;
}

void Client::play() {
    std::string command;
    bool playing = true;
    while (playing) {

        command = ask_for_command();
        std::istringstream ss(command);
        std::string action;
        ss >> action;

        if (action == "Exit") {
            playing = false;
            // break;
        } else if (action == "Chat") {
            std::vector<std::variant<uint8_t, uint16_t>> parsed_msg =
                    this->parser.parse_send_msg(command);
            protocol.client_send_msg(parsed_msg);
        } else if (action == "Read") {
            int amount_msgs;
            ss >> amount_msgs;

            while (amount_msgs > 0) {
                std::string msg = this->protocol.recv_msg();
                if (msg.length() == 0) {
                    // Cuando no hay mas mensajes, nunca entra aca. DESP CHEQUEAR
                    std::cout << "No hay mas mensajes para leer" << std::endl;
                    // playing = false;
                    break;
                } else {
                    std::cout << msg << std::endl;
                    amount_msgs--;
                }
            }
        }
    }
}

Client::~Client() {}
