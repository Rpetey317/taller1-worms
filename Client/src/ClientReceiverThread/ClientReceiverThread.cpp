#include "ClientReceiverThread.h"

#include "LibError.h"
#include "NetworkProtocol.h"

using NetworkProtocol::MSGCODE_PLAYER_AMOUNT;
using NetworkProtocol::MSGCODE_PLAYER_MESSAGE;
using NetworkProtocol::msgcode_t;

ReceiverThread::ReceiverThread(Queue<std::shared_ptr<Event>>& incomingq, ClientProtocol& prot):
        incomingq(incomingq), prot(prot) {}

void ReceiverThread::run() {
    while (_keep_running) {
        try {
            std::shared_ptr<Event> event(prot.recv_update());
            this->incomingq.push(event);
        } catch (LibError& e) {
            // This is a "socket was closed" error
            // i.e.: not an error, just someone closing connection from another thread
            _keep_running = false;
            this->incomingq.close();
            continue;
        } catch (ClosedQueue& e) {
            _keep_running = false;
            continue;
        } catch (...) {
            std::cerr << "Unexpected error in receiver thread" << std::endl;
        }
    }
}

void ReceiverThread::end() {
    _keep_running = false;
    this->incomingq.close();
    this->prot.close();
    _is_alive = false;
}

ReceiverThread::~ReceiverThread() {}
