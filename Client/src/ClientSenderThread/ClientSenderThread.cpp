#include "ClientSenderThread.h"

SenderThread::SenderThread(Queue<Action*>& outgoingq, ClientProtocol& prot):
        outgoingq(outgoingq), prot(prot) {}

void SenderThread::run() {
    while (_keep_running) {
        try {
            Action* action = outgoingq.pop();
            std::cout << "tamos de chill" << std::endl;
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
}

SenderThread::~SenderThread() {}
