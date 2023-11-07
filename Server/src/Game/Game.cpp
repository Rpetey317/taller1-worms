#include "Game.h"

#include <memory>
#include <utility>

#include "ReceiverThread.h"
#include "SenderThread.h"

GameHandler::GameHandler(Queue<ClientUpdate*>& _eventq): plcount(0), eventq(_eventq) {
    curr_pl = this->players.begin();
    next_free_id = 0;
}
// GameHandler::GameHandler(Queue<ClientUpdate*>& _eventq, int code): plcount(0), eventq(_eventq),
// game_code(code) {
//     curr_pl = this->players.begin();
// }

void GameHandler::add_player(Socket&& peer) {
    PlayerHandler* new_player =
            new PlayerHandler(std::move(peer), this->plcount, this->eventq, ++next_free_id);
    this->players.push_back(new_player);

    new_player->start();
}

void GameHandler::remove_disconnected() {
    std::cout << "Removing disconnected players" << std::endl;
    auto pl = this->players.begin();
    while (pl != this->players.end()) {
        if (!(*pl)->is_connected()) {
            delete (*pl);
            pl = this->players.erase(pl);
        }
        pl++;
    }
    std::cout << "Removed disconnected players!" << std::endl;
}

void GameHandler::advance_turn() {
    ++this->curr_pl;
    if (this->curr_pl == this->players.end()) {
        this->curr_pl = this->players.begin();
        // if (this->curr_pl == this->players.end()) {
        //     std::cout << "No players connected" << std::endl;
        //     return;
        // }

        // PlayerHandler* player = *curr_pl;
        // GameUpdate* update = new PlayerMessageUpdate("Your turn!"); // Es necesario el new?
        // Despues hay que hacer delete player->send(update);
    }
}


GameUpdate* GameHandler::execute(ClientUpdate* event) { return event->get_processed_by(*this); }

GameUpdate* GameHandler::process_disconnect(ClientDisconnectedUpdate& event) {
    return new PlayerDisconnectedUpdate(event.get_id());
}

GameUpdate* GameHandler::process_message(ClientMessageUpdate& event) {
    return new PlayerMessageUpdate(event.get_id(), event.get_msg());
}

void GameHandler::broadcast(GameUpdate* update) {
    std::cout << "Broadcasting update" << std::endl;
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++) {
        std::cout << "Sending update to player" << std::endl;
        (*pl)->send(update);
        std::cout << "Update sent" << std::endl;
    }
}

int GameHandler::count() { return plcount; }

void GameHandler::close() {
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++) delete (*pl);
}
