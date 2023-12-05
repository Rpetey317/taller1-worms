#include "ClientSenderThread.h"

#include <memory>

SenderThread::SenderThread(Queue<std::shared_ptr<Action>>& outgoingq, ClientProtocol& prot):
        outgoingq(outgoingq), prot(prot) {}

void SenderThread::run() {
    while (_keep_running) {
        try {
            std::shared_ptr<Action> action = outgoingq.pop();
            action->get_send_by(this->prot);
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
    this->outgoingq.close();
    _is_alive = false;
}

SenderThread::~SenderThread() {}
