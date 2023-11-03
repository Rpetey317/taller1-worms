#include "GameProcessing.h"

#include "NetworkProtocol.h"

#define CHAT_STR "Chat"
#define READ_STR "Read"
#define EXIT_STR "Exit"
#define NOCMD_STR ""

#define CHAT 0
#define READ 1
#define EXIT 2
#define NOCMD 3

using NetworkProtocol::msgcode_t;
using NetworkProtocol::MSGCODE_PLAYER_MESSAGE;

GameProcessing::GameProcessing(const char* hostname, const char* port):
        skt(Socket(hostname, port)),
        protocol(std::move(this->skt)),
        incomingq(),
        outgoingq(),
        receiverTh(incomingq, protocol),
        senderTh(outgoingq, protocol) {}

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

    // this->receiverTh.start();
    this->senderTh.start();

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
            this->outgoingq.push(new_chatmsg);
        } else if (cmd_id == READ) {
            int amount_msgs;
            ss >> amount_msgs;

            while (amount_msgs > 0) {
                msgcode_t code = this->protocol.recv_code();
                if (code == MSGCODE_PLAYER_MESSAGE) {
                    std::string rd_msg = this->protocol.recv_msg();
                    std::cout << rd_msg << std::endl;
                } else {
                    int amount_players = this->protocol.recv_amount_players();
                    std::cout << "Jugadores " << amount_players << ", esperando al resto de tus amigos..."
                              << std::endl;
                }
                amount_msgs --;
            }
        } // Puede haber distintos comandos.
    }
    // this->receiverTh.stop();
    this->senderTh.end();
    // this->receiverTh.join();
    this->senderTh.join();
}

GameProcessing::~GameProcessing() {}
