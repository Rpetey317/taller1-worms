#include "ReceiverThread.h"

#include <string>

#include "ClientUpdate.h"
#include "LibError.h"

ReceiverThread::ReceiverThread(Queue<ClientUpdate>& _eventq, ServerProtocol& _prot,
                               std::atomic<int>& _plcount):
        eventq(_eventq), prot(_prot), plcount(_plcount) {}

void ReceiverThread::run() {
    while (_keep_running) {
        try {
            ClientUpdate msg = prot.recv_msg();
            if (true /*msg.is_valid()*/) {
                this->eventq.push(msg);
            } else {
                // Protocol was closed
                // To be implemented
            }
        } catch (LibError& e) {
            // This is a "socket was closed" error
            // i.e.: not an error, just someone closing connection from another thread
            _keep_running = false;
            continue;
        } catch (...) {
            std::cerr << "Unexpected error in receiver thread" << std::endl;
        }
    }
}

void ReceiverThread::end() { _keep_running = false; }
