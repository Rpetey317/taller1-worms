#include "ReceiverThread.h"

#include <memory>
#include <string>

#include "LibError.h"
#include "Message.h"

ReceiverThread::ReceiverThread(Queue<std::shared_ptr<Message>>& _eventq, ServerProtocol& _prot,
                               const int& _plid):
        eventq(_eventq), prot(_prot), plid(_plid) {}

void ReceiverThread::run() {
    while (_keep_running && this->prot.is_connected()) {
        try {

            std::shared_ptr<Message> msg = prot.recv_update();
            if (msg->is_valid())
                this->eventq.push(msg);

        } catch (LibError& e) {
            // This is a "socket was closed" error
            // i.e.: not an error, just someone closing connection from another thread
            _keep_running = false;
            continue;
        } catch (...) {
            std::cerr << "Unexpected error in receiver thread" << std::endl;
        }
    }
    std::cout << "Player disconnected" << std::endl;
    this->eventq.push(std::make_shared<PlayerDisconnectedMessage>(this->plid));
}

void ReceiverThread::end() { _keep_running = false; }
