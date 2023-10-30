#include "PlayerHandler.h"

#include <utility>

PlayerHandler::PlayerHandler(Socket&& _peer, std::atomic<int>& _plcount,
                             Queue<ClientUpdate>& _eventq):
        prot(std::move(_peer)), sendq(), send_th(sendq, prot), recv_th(_eventq, prot, _plcount) {
    _plcount++;
    // recvers.push_to_all(ServerMessage(_plcount));
}

void PlayerHandler::start() {
    this->send_th.start();
    this->recv_th.start();
}

bool PlayerHandler::is_connected() { return prot.is_connected(); }

void PlayerHandler::send(const ClientUpdate& msg) { 
    sendq.push((GameUpdate*)(new PlayerMessageUpdate(msg.get_msg()))); 
    }

PlayerHandler::~PlayerHandler() {
    prot.close();

    send_th.end();
    send_th.join();

    recv_th.end();
    recv_th.join();
}
