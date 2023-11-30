#include "AccepterThread.h"

#include <utility>

#include "LibError.h"
#include "ServerProtocol.h"

ServerAccepterThread::ServerAccepterThread(Socket&& _acc, Game& _players):
        acc(std::move(_acc)), lobby(_players) {}

void ServerAccepterThread::run() {
    // GamesHandler lobby;
    while (_keep_running) {
        try {
            Socket peer = acc.accept();
            ServerProtocol prot(std::move(peer));
            this->lobby.add_player(std::move(prot));
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
