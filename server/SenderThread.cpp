#include "server_sender.h"

SenderThread::SenderThread(Queue<ServerMessage>& _sendq, ServerProtocol& _prot):
        sendq(_sendq), prot(_prot) {}

void SenderThread::run() {
    while (_keep_running) {
        try {
            ServerMessage msg = sendq.pop();

            // done here to avoid sending '0 players left'
            // (won't get received by player but will show up in tiburoncin)
            if (!this->prot.is_connected()) {
                _keep_running = false;
                continue;
            }
            switch (msg.flag) {
                case COUNT:
                    this->prot.send_plcount(msg.count);
                    break;

                case MSG:
                    this->prot.send_msg(msg.msg);
                    break;

                default:
                    break;
            }
        } catch (ClosedQueue& e) {
            _keep_running = false;
            continue;
        } catch (...) {
            std::cerr << "Unexpected error in sender thread" << std::endl;
        }
    }
}

void SenderThread::end() {
    _keep_running = false;
    this->sendq.close();
}
