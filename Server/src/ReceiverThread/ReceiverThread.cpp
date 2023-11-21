#include "ReceiverThread.h"

#include <memory>
#include <string>

#include "ClientUpdate.h"
#include "LibError.h"

ReceiverThread::ReceiverThread(Queue<ClientUpdate*>& _eventq, ServerProtocol& _prot,
                               const int& _plid):
        eventq(_eventq), prot(_prot), plid(_plid) {}

void ReceiverThread::run() {
    while (_keep_running) {
        try {

            ClientUpdate* msg = prot.recv_update();

            if (msg->is_valid()) {
                std::cout <<"Recibo mensaje valido" << std::endl;
                this->eventq.push(msg);
            } else {
                _keep_running = false;
                continue;
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

    // Player disconnected
    this->eventq.push((ClientUpdate*)new ClientDisconnectedUpdate(this->plid));
}

void ReceiverThread::end() { _keep_running = false; }
