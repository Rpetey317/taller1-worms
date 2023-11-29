#include "SenderThread.h"

#include <memory>

#include "Update.h"

SenderThread::SenderThread(Queue<std::shared_ptr<Update>>& _sendq, ServerProtocol& _prot):
        sendq(_sendq), prot(_prot) {}

void SenderThread::run() {
    while (_keep_running) {
        try {
            std::shared_ptr<Update> msg = sendq.pop();

            // done here to avoid sending '0 players left'
            // (won't get received by player but will show up in tiburoncin)
            if (!this->prot.is_connected()) {
                _keep_running = false;
                continue;
            }
            if (this->prot.send_update(msg) == CLOSED_SKT) {
                _keep_running = false;
                continue;
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
