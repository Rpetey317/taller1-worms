#include "Game.h"

#include <list>
#include <memory>
#include <utility>

#include "CommonMapParser/CommonMapParser.h"

#include "ReceiverThread.h"
#include "SenderThread.h"

int ttime = 15;

Game::Game(Queue<std::shared_ptr<Message>>& _eventq, const std::string& _name):
        plcount(0),
        eventq(_eventq),
        game_code(0),
        next_free_id(0),
        box2d_in(10000),
        box2d_out(10000),
        turn_start(std::chrono::steady_clock::now()),
        turn_time(ttime),
        worm_count(0),
        current_worm(std::make_pair(0, 0)),
        box2d(_name) {
    curr_pl = this->players.begin();
    CommonMapParser parser;
    parser.get_map(_name);
    this->worm_count = parser.get_amount_of_worms();
}

void Game::add_player(ServerProtocol&& peer) {
    std::lock_guard<std::mutex> lock(this->plmtx);
    PlayerHandler* new_player = new PlayerHandler(std::move(peer), this->eventq, ++next_free_id);
    this->players.insert(std::make_pair(next_free_id, std::unique_ptr<PlayerHandler>(new_player)));
    this->plcount++;
}

void Game::add_host(ServerProtocol&& peer) {
    std::lock_guard<std::mutex> lock(this->plmtx);
    PlayerHandler* new_player = new PlayerHandler(std::move(peer), this->eventq, ++next_free_id);
    this->players.insert(std::make_pair(next_free_id, std::unique_ptr<PlayerHandler>(new_player)));
    this->host = this->players.find(next_free_id);
}

// DD methods implemented in Game_processUpdate.cpp
std::shared_ptr<Update> Game::execute(std::shared_ptr<Message> event) {
    return event->get_processed_by(*this);
}

void Game::broadcast(std::shared_ptr<Update> update) {
    std::lock_guard<std::mutex> lock(this->plmtx);
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++) {
        (*pl).second->send(update);
    }
}

int Game::count() { return plcount; }

bool Game::recv_host_start() { return this->host->second->recv_start(); }

void Game::divide_worms() {
    std::map<int, std::unique_ptr<PlayerHandler>>::iterator it = players.begin();
    for (int j = 0; j < worm_count; j++) {
        if (it == players.end()) {
            it = players.begin();
        }
        it->second->assign_worm(j + 1);
        ++it;
    }

    it = players.begin();
    while (it != players.end()) {
        std::list<int> worms = it->second->get_worms();
        for (auto worm_id: worms) {
            box2d.set_teams(worm_id, it->first);
        }
        ++it;
    }
}

void Game::start() {
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++) (*pl).second->start();
}

void Game::tick_box2d() { this->box2d.tick(); }

void Game::reset_timer() { turn_start = std::chrono::steady_clock::now(); }

void Game::close() {
    for (auto pl = this->players.begin(); pl != this->players.end(); pl++)
        delete (*pl).second.release();
}
