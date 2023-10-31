#include "Game.h"

#include <utility>

#include "ReceiverThread.h"
#include "SenderThread.h"

GameHandler::GameHandler(Queue<ClientUpdate>& _eventq): plcount(0), eventq(_eventq) {
    curr_pl = this->players.begin();
}

void GameHandler::add_player(Socket&& peer) {
    PlayerHandler* new_player = new PlayerHandler(std::move(peer), this->plcount, this->eventq);
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

void GameHandler::advance_turn() {
    ++this->curr_pl;
    if (this->curr_pl == this->players.end())
        this->curr_pl = this->players.begin();
}


GameUpdate* GameHandler::execute(ClientUpdate& event) {
    return new PlayerMessageUpdate(event.get_msg());
}

void GameHandler::broadcast(GameUpdate* update) {
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++) {
        (*pl)->send(update);
    }
}

int GameHandler::count() { return plcount; }

void GameHandler::close() {
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++) delete (*pl);
}
