#include <utility>

#include "server_plhandler.h"

PlayerHandler::PlayerHandler(Socket&& _peer, std::atomic<int>& _plcount,
                             ReceiverListMonitor& _recvers):
        prot(std::move(_peer)),
        sendq(),
        recvers(_recvers),
        send_th(sendq, prot),
        recv_th(recvers, prot, _plcount) {
    recvers.add_recver(&sendq);
    _plcount++;
    recvers.push_to_all(ServerMessage(_plcount));
}

void PlayerHandler::start() {
    this->send_th.start();
    this->recv_th.start();
}

bool PlayerHandler::is_connected() { return prot.is_connected(); }

void PlayerHandler::send(const ServerMessage& msg) { sendq.push(msg); }

PlayerHandler::~PlayerHandler() {
    prot.close();

    send_th.end();
    send_th.join();

    recv_th.end();
    recv_th.join();
}
