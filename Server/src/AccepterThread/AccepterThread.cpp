#include "AccepterThread.h"

#include <utility>

#include "LibError.h"

ServerAccepterThread::ServerAccepterThread(Socket&& _acc):
        acc(std::move(_acc)) {}

void ServerAccepterThread::run() {
    GamesHandler lobby;
    while (_keep_running) {
        try {
            Socket peer = acc.accept();
            lobby.add_player(std::move(peer));
            lobby.remove_disconnected();
            // std::cout << "Player connected. Current player count: " << this->lobby.count()
            //           << std::endl;
        } catch (LibError& e) {
            // This is a "socket was closed" error
            // (i.e. not really an error, just someone calling this->end)
            return;
        }
    }
}

void ServerAccepterThread::end() {
    this->_keep_running = false;
    this->acc.shutdown(2);
    this->acc.close();
}

ServerAccepterThread::~ServerAccepterThread() {}
