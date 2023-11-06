#include "Game.h"

#include <utility>

#include "ReceiverThread.h"
#include "SenderThread.h"

// GameHandler::GameHandler(Queue<ClientUpdate*>& _eventq): plcount(0), eventq(_eventq) {
//     curr_pl = this->players.begin();
// }
GameHandler::GameHandler(Queue<ClientUpdate*>& _eventq, size_t code): plcount(0), eventq(_eventq), game_code(code) {
    curr_pl = this->players.begin();

}

void GameHandler::add_player(Socket&& peer) {
    PlayerHandler* new_player = new PlayerHandler(std::move(peer), this->plcount, this->eventq);
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
    if (this->curr_pl == this->players.end()){
        this->curr_pl = this->players.begin();
        // if (this->curr_pl == this->players.end()) {
        //     std::cout << "No players connected" << std::endl;
        //     return;
        // }
        
        // PlayerHandler* player = *curr_pl;
        // GameUpdate* update = new PlayerMessageUpdate("Your turn!"); // Es necesario el new? Despues hay que hacer delete
        // player->send(update);
    }
}


GameUpdate* GameHandler::execute(ClientUpdate* event) {
    std::cout << "Executing event" << std::endl;
    PlayerMessageUpdate* ret = new PlayerMessageUpdate(event->get_msg());
    delete event;
    std::cout << "Update created" << std::endl;
    return ret;
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
