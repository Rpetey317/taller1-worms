#include "ClientSenderThread.h"

SenderThread::SenderThread(Queue<Action>& outgoingq, ClientProtocol& prot):
        outgoingq(outgoingq), prot(prot) {}

void SenderThread::run() {
    while (_keep_running) {
        try {
            Action action;
            action = this->outgoingq.pop();
            // Todo este if deberia ir en un parser o no?
            this->prot.send_code(action.type_action);
            if (action.type_action == 0x01) {  // Create
                /* code */
            } else if (action.type_action == 0x02) {  // Join
                this->prot.send_code_game(action.code_game);
            } else if (action.type_action == 0x09) {  // Chat
                this->prot.send_msg(action.msg);
            }
            // this->prot.client_send_msg(action.type_action, action.msg);
        } catch (ClosedQueue& e) {
            _keep_running = false;
            continue;
        } catch (...) {
            std::cerr << "Unexpected error in sender thread" << std::endl;
        }
    }
}

void SenderThread::end() {
    _keep_running = false;
    this->outgoingq.close();
}

SenderThread::~SenderThread() {}
