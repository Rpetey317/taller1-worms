#include "ClientReceiverThread.h"

ReceiverThread::ReceiverThread(Queue<std::string>& incomingq, ClientProtocol& prot) : incomingq(incomingq), prot(prot) {}

void ReceiverThread::run() {}

void ReceiverThread::end() { 
    _keep_running = false; 
}

ReceiverThread::~ReceiverThread() {}
