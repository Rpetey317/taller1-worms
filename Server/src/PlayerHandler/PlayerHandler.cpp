#include "PlayerHandler.h"

#include <utility>

#include "NetworkProtocol.h"

using NetworkProtocol::MSGCODE_ACK;             // MGSCODE_CREATE_GAME
using NetworkProtocol::MSGCODE_PLAYER_CONNECT;  // MSGCODE_PLAYER_CONNECT_TO_GAME
using NetworkProtocol::msgcode_t;

PlayerHandler::PlayerHandler(ServerProtocol&& _peer, Queue<std::shared_ptr<Message>>& _eventq,
                             int& _id):
        prot(std::move(_peer)),
        sendq(10000),
        send_th(sendq, prot),
        recv_th(_eventq, prot, _id),
        id(_id) {
    std::shared_ptr<PlayerAcknowledge> ack = std::make_shared<PlayerAcknowledge>(_id);
    this->prot.send_update(ack);
    _eventq.push(std::make_shared<PlayerConnectedMessage>(_id));
}

void PlayerHandler::start() {

    // msgcode_t request = this->prot.recv_request();
    // if (request == MSGCODE_CREATE_GAME) {
    //     int code = 0;
    //     // Create game. Esto deberia ir en el constructor de Game (?)
    //     std::cout << "Created match: " << std::to_string(code) << std::endl;
    // } else if (request == MSGCODE_PLAYER_CONNECT_TO_GAME) {
    //     int code = this->prot.recv_join();
    //     int8_t join_result = OK;

    //     try {
    //         // Agregar al jugador a la partida. Tmb en el Game (?)
    //     } catch (const std::exception& err) {
    //         if (std::string(err.what()) == "El codigo ingresado no pertenece a ninguna partida!")
    //         {
    //             join_result = FAILURE;
    //         }
    //     }

    //     this->prot.send_join_result(join_result);

    //     if (join_result == OK) {
    //         std::cout << "Joined to match: " << std::to_string(code) << std::endl;
    //     } else {
    //         std::cout << "Match does not exist: " << std::to_string(code) << std::endl;
    //     }
    // }

    this->send_th.start();
    this->recv_th.start();
}

bool PlayerHandler::is_connected() { return prot.is_connected(); }

void PlayerHandler::send(std::shared_ptr<Update> msg) { sendq.push(msg); }

PlayerHandler::~PlayerHandler() {
    prot.close();

    send_th.end();
    send_th.join();

    recv_th.end();
    recv_th.join();
}
