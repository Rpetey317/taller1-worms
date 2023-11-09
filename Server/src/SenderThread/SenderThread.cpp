#include "SenderThread.h"

#include "GameUpdate.h"

SenderThread::SenderThread(Queue<GameUpdate*>& _sendq, ServerProtocol& _prot):
        sendq(_sendq), prot(_prot) {}

void SenderThread::run() {
    while (_keep_running) {
        try {
            GameUpdate* msg = sendq.pop();

            // done here to avoid sending '0 players left'
            // (won't get received by player but will show up in tiburoncin)
            if (!this->prot.is_connected()) {
                _keep_running = false;
                continue;
            }
            std::cout << "trying to send smth" << std::endl;
            this->prot.send_update(msg);
        } catch (ClosedQueue& e) {
            std::cout << "Sender queue closed" << std::endl;
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
