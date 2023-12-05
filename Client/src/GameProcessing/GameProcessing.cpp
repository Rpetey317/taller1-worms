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

GameProcessing::GameProcessing(ClientProtocol& protocol, Queue<std::shared_ptr<Action>>& commands,
                               Queue<std::shared_ptr<Event>>& events):
        protocol(protocol),

        outgoingq(commands),
        incomingq(events),
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

    std::shared_ptr<Event> ack_update =
            this->protocol.recv_update();  // Va a ser player connected. Me devuelve mi id
    std::shared_ptr<PlayerConnected> connected =
            std::dynamic_pointer_cast<PlayerConnected>(ack_update);
    this->id = connected->get_id();
    if (id < 0) {
        throw std::runtime_error("Error al recibir el id del jugador");
    }
    incomingq.push(ack_update);
    std::cout << "Player id: " << this->id << std::endl;

    this->receiverTh.start();
    this->senderTh.start();
}

int GameProcessing::get_id() { return this->id; }

void GameProcessing::end() {
    this->receiverTh.end();
    this->senderTh.end();
    this->receiverTh.join();
    this->senderTh.join();
}

GameProcessing::~GameProcessing() {}
