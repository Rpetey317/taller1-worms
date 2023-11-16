#include "Game.h"

#include <memory>
#include <utility>

#include "ReceiverThread.h"
#include "SenderThread.h"

GameHandler::GameHandler(Queue<ClientUpdate*>& _eventq):
        plcount(0),
        eventq(_eventq),
        game_code(0),
        next_free_id(0),
        box2d_in(10000),
        box2d_out(10000),
        box2d(box2d_in, box2d_out) {
    curr_pl = this->players.begin();
}

void GameHandler::add_player(Socket&& peer) {
    PlayerHandler* new_player = new PlayerHandler(std::move(peer), this->eventq, ++next_free_id);
    this->players.insert(std::make_pair(next_free_id, std::unique_ptr<PlayerHandler>(new_player)));
    new_player->start();
}

// DD methods implemented in Game_processUpdate.cpp
GameUpdate* GameHandler::execute(ClientUpdate* event) { return event->get_processed_by(*this); }

void GameHandler::broadcast(GameUpdate* update) {
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++) {
        (*pl).second->send(update);
    }
}

int GameHandler::count() { return plcount; }

void GameHandler::close() {
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++)
        delete (*pl).second.release();
}
