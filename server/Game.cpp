#include <utility>

#include "server_gamehandler.h"
#include "server_receiver.h"
#include "server_sender.h"

GameHandler::GameHandler(ReceiverListMonitor& _recvers): plcount(0), recvers(_recvers) {}

void GameHandler::add_player(Socket&& peer) {
    PlayerHandler* new_player = new PlayerHandler(std::move(peer), this->plcount, this->recvers);
    this->players.push_back(new_player);

    new_player->start();
}

void GameHandler::remove_disconnected() {
    auto pl = this->players.begin();
    while (pl != this->players.end()) {
        if (!(*pl)->is_connected()) {
            delete (*pl);
            pl = this->players.erase(pl);
        }
        pl++;
    }
}

int GameHandler::count() { return plcount; }

void GameHandler::close() {
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++) delete (*pl);
}
