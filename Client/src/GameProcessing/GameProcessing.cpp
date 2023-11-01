#include "GameProcessing.h"

#define CHAT_STR "Chat"
#define READ_STR "Read"
#define EXIT_STR "Exit"
#define NOCMD_STR ""

#define CHAT 0
#define READ 1
#define EXIT 2
#define NOCMD 3


GameProcessing::GameProcessing(const char* hostname, const char* port):
        skt(Socket(hostname, port)), protocol(std::move(this->skt)) {}

std::string GameProcessing::ask_for_command() {
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

void GameProcessing::run() {
    // Creo los threads sender y receiver pasandoles el protocolo y los corro

    const std::map<std::string, int> lut{
            {CHAT_STR, CHAT},
            {READ_STR, READ},
            {EXIT_STR, EXIT},
            {NOCMD_STR, NOCMD},
    };

    bool playing = true;
    std::string command;
    while (playing) {

        command = ask_for_command();
        std::istringstream ss(command);
        std::string action;
        ss >> action;
        int cmd_id = lut.at(action);
        if (cmd_id == EXIT) {
            playing = false;
            // break;
        } else if (cmd_id == CHAT) {
            std::string chatmsg;
            std::getline(ss, chatmsg);
            int lenght;
            lenght = chatmsg.size();
            int position = 0;
            while (isblank(chatmsg[position])) {  // Quiero empezar a leer cuando se encuentre la
                                                  // primera letra
                position++;
                lenght--;  // Quito el espacio blanco
            }
            std::string new_chatmsg = chatmsg.substr(position);
            protocol.client_send_msg(new_chatmsg);
        } else if (cmd_id == READ) {
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

GameProcessing::~GameProcessing() {}
