#include "GameProcessing.h"

#include <list>

#include "../Event/EventHeaders.h"  // Esto desp lo borro. El evento lo deberia procesar el EventProcessor

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

using NetworkProtocol::MSGCODE_PLAYER_AMOUNT;
using NetworkProtocol::MSGCODE_PLAYER_MESSAGE;
using NetworkProtocol::msgcode_t;

GameProcessing::GameProcessing(const char* hostname, const char* port):
        skt(Socket(hostname, port)),
        protocol(std::move(this->skt)),
        incomingq(10000),
        outgoingq(10000),
        receiverTh(incomingq, protocol),  // pass the expected arguments to the constructor
        senderTh(outgoingq, protocol),
        id(0) {}

std::string GameProcessing::ask_for_command() {
    std::string command;
    std::getline(std::cin, command);
    std::istringstream s(command);
    std::string action;
    s >> action;
    if (action != "Chat" && action != "Read" && action != "Exit" && action != "Create" &&
        action != "Join") {
        std::getline(std::cin, command);
        std::istringstream s_new(command);
        s_new >> action;
    }
    return command;
}

void GameProcessing::run() {
    // Creo los threads sender y receiver pasandoles el protocolo y los corro

    const std::map<std::string, int> lut{
            {CREATE_STR, CREATE}, {JOIN_STR, JOIN}, {CHAT_STR, CHAT},
            {READ_STR, READ},     {EXIT_STR, EXIT}, {NOCMD_STR, NOCMD},
    };

    Event* ack_update =
            this->protocol.recv_update();  // Va a ser player connected. Me devuelve mi id
    PlayerConnected* connected = dynamic_cast<PlayerConnected*>(ack_update);
    this->id = connected->get_id();
    if (id < 0) {
        throw std::runtime_error("Error al recibir el id del jugador");
    }
    std::cout << "Player id: " << this->id << std::endl;

    this->receiverTh.start();
    this->senderTh.start();

    bool playing = true;
    std::string command;
    while (playing) {
        // pop.commands()
        // 
        std::list<Event*> update_list;

        bool popped = false;
        do {
            Event* upd;
            popped = this->incomingq.try_pop(upd);
            if (popped)
                update_list.push_back(upd);
        } while (popped);

        for (auto upd: update_list) {
            std::cout << "Popped an event" << std::endl;
            this->eventProcessor.proccess_event(upd);
        }

        command = ask_for_command();
        std::istringstream ss(command);
        std::string action_str;
        ss >> action_str;
        int cmd_id = lut.at(action_str);
        if (cmd_id == EXIT) {
            playing = false;
            // break;
        } else if (cmd_id == CREATE) {
            // Action create_game(CREATE, "");
            // this->outgoingq.push(create_game);
        } else if (cmd_id == JOIN) {
            /* code */
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
            // Action new_action(MSGCODE_PLAYER_MESSAGE, new_chatmsg);
            std::string new_chatmsg = chatmsg.substr(position);
            Message* action = new Message(new_chatmsg);
            this->outgoingq.push(action);
        } else if (cmd_id == READ) {
            int amount_msgs;
            ss >> amount_msgs;

            while (amount_msgs > 0) {
                Event* popped_update = this->incomingq.pop();
                PlayerMessage* msg = dynamic_cast<PlayerMessage*>(
                        popped_update);  // TODO: ver si esto esta bien. Por ahora se que es un
                                         // PlayerMessage action
                if (msg != nullptr && msg->get_msg() != "")
                    std::cout << msg->get_msg() << std::endl;

                amount_msgs--;
            }
        }  // Puede haber distintos comandos.
    }
    this->receiverTh.end();
    this->receiverTh.join();
    this->senderTh.end();
    this->senderTh.join();
}

GameProcessing::~GameProcessing() {}
