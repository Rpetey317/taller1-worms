#include "Game.h"

#include <memory>
#include <utility>

#include "ReceiverThread.h"
#include "SenderThread.h"

GameHandler::GameHandler(Queue<ClientUpdate*>& _eventq): plcount(0), eventq(_eventq), game_code(0) {
    curr_pl = this->players.begin();
    next_free_id = 0;
}

void GameHandler::add_player(Socket&& peer) {
    PlayerHandler* new_player = new PlayerHandler(std::move(peer), this->eventq, ++next_free_id);
    this->players.push_back(new_player);
    this->plcount++;
    new_player->start();
}

void GameHandler::remove_disconnected() {
    auto pl = this->players.begin();
    while (pl != this->players.end()) {
        if (!(*pl)->is_connected()) {
            delete (*pl);
            pl = this->players.erase(pl);
            this->plcount--;
        }
        pl++;
    }
}

void GameHandler::advance_turn() {
    ++this->curr_pl;
    if (this->curr_pl == this->players.end()) {
        this->curr_pl = this->players.begin();
    }
    // todo: send turn change update
}

// DD methods implemented in Game_processUpdate.cpp
GameUpdate* GameHandler::execute(ClientUpdate* event) { return event->get_processed_by(*this); }

void GameHandler::broadcast(GameUpdate* update) {
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++) {
        (*pl)->send(update);
    }
}

int GameHandler::count() { return plcount; }

void GameHandler::close() {
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++) delete (*pl);
}
