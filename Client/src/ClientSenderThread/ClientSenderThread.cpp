#include "ClientSenderThread.h"

SenderThread::SenderThread(Queue<std::string>& outgoingq, ClientProtocol& prot):
        outgoingq(outgoingq), prot(prot) {}

void SenderThread::run() {
    while (_keep_running) {
        try {
            std::string msg = this->outgoingq.pop();
            this->prot.client_send_msg(msg);
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
