#include "AccepterThread.h"

#include <utility>

#include "LibError.h"
#include "ServerProtocol.h"

ServerAccepterThread::ServerAccepterThread(Socket&& _acc, LobbyHandler& _handler):
        acc(std::move(_acc)), handler(_handler) {}

void ServerAccepterThread::reap_players() {
    for (auto it = connecting_players.begin(); it != connecting_players.end(); ++it) {
        if ((*it)->is_dead()) {
            (*it)->stop();
            (*it)->join();
            it = connecting_players.erase(it);
        }
    }
}

void ServerAccepterThread::run() {
    // GamesHandler lobby;
    while (_keep_running) {
        try {
            Socket peer = acc.accept();
            std::unique_ptr<LobbyHandlerThread> player_th(
                    new LobbyHandlerThread(std::move(peer), handler));
            player_th->start();
            connecting_players.push_back(std::move(player_th));  // is this gonna break???
            this->reap_players();
        } catch (LibError& e) {
            // This is a "socket was closed" error
            // (i.e. not really an error, just someone calling this->end)
            return;
        }
    }
}

void ServerAccepterThread::end() {
    this->_keep_running = false;
    for (auto& player: connecting_players) {
        player->stop();
        player->join();
    }

    this->acc.shutdown(2);
    this->acc.close();
}

ServerAccepterThread::~ServerAccepterThread() {}
