#include "GameProcessing.h"

#include "NetworkProtocol.h"

#define CREATE_STR "Create"
#define JOIN_STR "Join"
#define CHAT_STR "Chat"
#define READ_STR "Read"
#define EXIT_STR "Exit"
#define NOCMD_STR ""

#define CREATE 0
#define JOIN 1 
#define CHAT 2
#define READ 3
#define EXIT 4
#define NOCMD 5

using NetworkProtocol::msgcode_t;
using NetworkProtocol::MSGCODE_PLAYER_MESSAGE;
using NetworkProtocol::MSGCODE_PLAYER_AMOUNT;

GameProcessing::GameProcessing(const char* hostname, const char* port):
    skt(Socket(hostname, port)),
    protocol(std::move(this->skt)),
    incomingq(10000),
    outgoingq(10000),
    receiverTh(incomingq, protocol), // pass the expected arguments to the constructor
    senderTh(outgoingq, protocol) {}

std::string GameProcessing::ask_for_command() {
    std::string command;
    std::getline(std::cin, command);
    std::istringstream s(command);
    std::string action;
    s >> action;
    while (action != "Chat" && action != "Read" && action != "Exit" && action != "Create" && action != "Join") {
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
            {CREATE_STR, CREATE},
            {JOIN_STR, JOIN},
            {CHAT_STR, CHAT},
            {READ_STR, READ},
            {EXIT_STR, EXIT},
            {NOCMD_STR, NOCMD},
    };

    this->receiverTh.start();
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
        } else if (cmd_id == CREATE) {
            std::cout << "Entro aca 0 " << std::endl;
            Action create_game(CREATE, "");
            this->outgoingq.push(create_game);
        } else if (cmd_id == JOIN) {

            std::cout << "Entro aca 1 " << std::endl;
            /* code */
        } else if (cmd_id == CHAT) {

            std::cout << "Entro aca 2 " << std::endl;
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
            Action new_action(MSGCODE_PLAYER_MESSAGE, new_chatmsg);
            this->outgoingq.push(new_action);
        } else if (cmd_id == READ) {

            std::cout << "Entro aca 3 " << std::endl;
            int amount_msgs;
            ss >> amount_msgs;

            while (amount_msgs > 0) {
                Action action = this->incomingq.pop();
                if (action.msg != "") {
                    std::cout << action.msg << std::endl;
                }
                amount_msgs --;
            }
        } // Puede haber distintos comandos.
    }
    this->receiverTh.end();
    this->receiverTh.join();
    this->senderTh.end();
    this->senderTh.join();
}

GameProcessing::~GameProcessing() {}