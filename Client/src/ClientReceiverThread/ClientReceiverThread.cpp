#include "ClientReceiverThread.h"

#include "LibError.h"
#include "NetworkProtocol.h"

using NetworkProtocol::MSGCODE_PLAYER_AMOUNT;
using NetworkProtocol::MSGCODE_PLAYER_MESSAGE;
using NetworkProtocol::msgcode_t;

ReceiverThread::ReceiverThread(Queue<Action>& incomingq, ClientProtocol& prot):
        incomingq(incomingq), prot(prot) {}

void ReceiverThread::run() {
    while (_keep_running) {
        try {
            Action action;
            msgcode_t code = this->prot.recv_code();
            if (code == MSGCODE_PLAYER_MESSAGE) {
                action.msg = this->prot.recv_msg();
            } else if (code == MSGCODE_PLAYER_AMOUNT) {
                int amount_players = this->prot.recv_amount_players();
                action.msg = "Jugadores " + std::to_string(amount_players) +
                             ", esperando al resto de tus amigos...";
            }
            this->incomingq.push(action);
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
}

ReceiverThread::~ReceiverThread() {}
