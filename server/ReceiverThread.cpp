#include <string>

#include "../common_src/common_ext_liberror.h"

#include "server_receiver.h"

ReceiverThread::ReceiverThread(ReceiverListMonitor& _recvers, ServerProtocol& _prot,
                               std::atomic<int>& _plcount):
        recvers(_recvers), prot(_prot), plcount(_plcount) {}

void ReceiverThread::run() {
    while (_keep_running) {
        try {
            std::string msg = prot.recv_msg();
            if (msg != NO_MSG_RECV) {
                this->recvers.push_to_all(ServerMessage(msg));
            } else {
                // Protocol was closed
                plcount--;
                this->recvers.push_to_all(ServerMessage(plcount));
                _keep_running = false;
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
