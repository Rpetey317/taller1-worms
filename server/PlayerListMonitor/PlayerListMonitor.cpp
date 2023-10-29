#include "PlayerListMonitor.h"

#include <iostream>

void print_msg(const GameUpdate* upd) { std::cout << upd->get_msg() << std::endl; }

ReceiverListMonitor::ReceiverListMonitor() {}

void ReceiverListMonitor::add_recver(Queue<GameUpdate*>* recver) {
    std::lock_guard<std::mutex> lck(mtx);
    this->recvers.push_back(recver);
}

void ReceiverListMonitor::push_to_all(GameUpdate* msg) {
    print_msg(msg);
    std::lock_guard<std::mutex> lck(mtx);
    for (auto q = this->recvers.begin(); q != this->recvers.end(); q++) {
        try {
            (*q)->push(msg);
        } catch (ClosedQueue& e) {
            q = recvers.erase(q);
            q--;
        }
    }
}

ReceiverListMonitor::~ReceiverListMonitor() {}
