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
        id(_id),
        assigned_worms(),
        last_worm_used(assigned_worms.end()) {
    std::shared_ptr<PlayerAcknowledge> ack = std::make_shared<PlayerAcknowledge>(_id);
    // This is for debugging purposes only, delete later
    if (_id % 2 == 0) {
        assigned_worms.push_back(2);
        assigned_worms.push_back(4);
    } else {
        assigned_worms.push_back(1);
        assigned_worms.push_back(3);
    }
    last_worm_used = assigned_worms.begin();

    this->prot.send_update(ack);
    _eventq.push(std::make_shared<PlayerConnectedMessage>(_id));
}

void PlayerHandler::start() {
    this->send_th.start();
    this->recv_th.start();
}

bool PlayerHandler::is_connected() { return prot.is_connected(); }

void PlayerHandler::send(std::shared_ptr<Update> msg) { sendq.push(msg); }

void PlayerHandler::advance_worm() {
    if (last_worm_used == assigned_worms.end()) {
        last_worm_used = assigned_worms.begin();
        return;
    }
    ++last_worm_used;
    if (last_worm_used == assigned_worms.end()) {
        last_worm_used = assigned_worms.begin();
    }
}

void PlayerHandler::assign_worm(int id) { assigned_worms.push_back(id); }

bool PlayerHandler::recv_start() {
    return this->prot.recv_game_start();
}

int PlayerHandler::get_current_worm() { return *last_worm_used; }

PlayerHandler::~PlayerHandler() {
    send_th.end();
    send_th.join();

    recv_th.end();
    recv_th.join();
}
