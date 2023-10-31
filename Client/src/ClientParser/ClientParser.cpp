#include "ClientParser.h"

ClientParser::ClientParser() {}

std::vector<std::variant<uint8_t, uint16_t>> ClientParser::parse_send_msg(std::string& command) {
    // Ya sabemos que la accion es Chat.
    std::vector<std::variant<uint8_t, uint16_t>> parsed_command;
    std::istringstream s(command);
    std::string action;
    s >> action;                                        // Ya sabemos que la accion es chat
    parsed_command.push_back(static_cast<uint8_t>(5));  // Aviso que es un comando Chat
    int lenght;
    std::string chatmsg;
    std::getline(s, chatmsg);
    lenght = chatmsg.size();
    int position = 0;
    while (isblank(
            chatmsg[position])) {  // Quiero empezar a leer cuando se encuentre la primera letra
        position++;
        lenght--;  // Quito el espacio blanco
    }
    uint16_t uint16_lenght = static_cast<uint16_t>(lenght);
    uint16_lenght = htons(uint16_lenght);
    parsed_command.push_back(uint16_lenght);

    for (int i = position; i < (lenght + position); i++) {
        uint8_t word_to_number = static_cast<uint8_t>(chatmsg[i]);
        parsed_command.push_back(word_to_number);
    }

    return parsed_command;
}

ClientParser::~ClientParser() {}