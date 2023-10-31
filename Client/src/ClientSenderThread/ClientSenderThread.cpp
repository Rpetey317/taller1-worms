#include "ClientSenderThread.h"

SenderThread::SenderThread(Queue<std::string>& outgoingq, ClientProtocol& prot) : outgoingq(outgoingq), prot(prot) {}

void SenderThread::run() {} //Hay que implementar

void SenderThread::end() {
    _keep_running = false;
    this->outgoingq.close();
}

SenderThread::~SenderThread() {}
