#include "server/Game/Game.h"

#include <utility>

#include "server/ReceiverThread/ReceiverThread.h"
#include "server/SenderThread/SenderThread.h"

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

GameUpdate* GameHandler::execute(ClientUpdate* event) { return new GameUpdate(event->get_msg()); }

void GameHandler::broadcast(GameUpdate* update) { this->recvers.push_to_all(update); }

int GameHandler::count() { return plcount; }

void GameHandler::close() {
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++) delete (*pl);
}
