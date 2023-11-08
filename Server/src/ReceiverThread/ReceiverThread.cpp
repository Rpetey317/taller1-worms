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

            std::unique_ptr<ClientMessageUpdate> msg =
                    std::make_unique<ClientMessageUpdate>(prot.recv_msg());

            if (msg->is_valid()) {
                std::cout << "Received message: " << msg->get_msg() << std::endl;
                this->eventq.push((ClientUpdate*)msg.release());
                std::cout << "Pushed message" << std::endl;
            } else {
                _keep_running = false;
                continue;
            }
        } catch (LibError& e) {
            // This is a "socket was closed" error
            // i.e.: not an error, just someone closing connection from another thread
            std::cout << "Socket closed, player " << this->plid << std::endl;
            _keep_running = false;
            continue;
        } catch (...) {
            std::cerr << "Unexpected error in receiver thread" << std::endl;
        }
    }

    // Player disconnected
    this->eventq.push((ClientUpdate*)new PlayerDisconnectedUpdate(this->plid));
}

void ReceiverThread::end() { _keep_running = false; }
