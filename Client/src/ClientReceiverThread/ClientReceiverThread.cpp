#include "ClientReceiverThread.h"

#include "LibError.h"
#include "NetworkProtocol.h"

using NetworkProtocol::msgcode_t;
using NetworkProtocol::MSGCODE_PLAYER_MESSAGE;
using NetworkProtocol::MSGCODE_PLAYER_AMOUNT;

ReceiverThread::ReceiverThread(Queue<std::string>& incomingq, ClientProtocol& prot):
        incomingq(incomingq), prot(prot) {}

void ReceiverThread::run() {
        while (_keep_running) {
                try {
                        std::string msg = "";
                        msgcode_t code = this->prot.recv_code();
                        if (code == MSGCODE_PLAYER_MESSAGE) {
                                msg = this->prot.recv_msg();
                        } else if (code == MSGCODE_PLAYER_AMOUNT) {
                                int amount_players = this->prot.recv_amount_players();
                                msg =  "Jugadores " + std::to_string(amount_players) + ", esperando al resto de tus amigos...";
                        }
                        this->incomingq.push(msg);
                } catch (LibError& e) {
                        // This is a "socket was closed" error
                        // i.e.: not an error, just someone closing connection from another thread
                        std::cout << "Socket was closed" << std::endl;
                        _keep_running = false;
                        this->incomingq.close();
                        continue;
                }catch (ClosedQueue& e) {
                        std::cout << "Queue was closed" << std::endl;
                        _keep_running = false;
                        continue;
                } 
                catch (...) {
                        std::cerr << "Unexpected error in receiver thread" << std::endl;
                }
        }
}

void ReceiverThread::end() { 
        std::cout << "Destroying receiver thread" << std::endl;
        _keep_running = false;
        this->incomingq.close();
        this->prot.close();
        std::cout << "Receiver thread destroyed" << std::endl;
}

ReceiverThread::~ReceiverThread() {}
