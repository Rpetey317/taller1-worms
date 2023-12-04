#include <chrono>
#include <iterator>
#include <memory>

#include "Game.h"

std::shared_ptr<Update> Game::process_disconnect(PlayerDisconnectedMessage& event) {
    // TODO: mark all associated worms as "dead"
    std::lock_guard<std::mutex> lock(this->plmtx);
    int disconnected_id = event.get_id();
    if (this->curr_pl->first == disconnected_id) {
        auto nx_pl = std::next(this->curr_pl);
        if (nx_pl == this->players.end()) {
            nx_pl = this->players.begin();
        }
        this->eventq.push(std::make_shared<TurnAdvance>(SERVER_ID, nx_pl->first));
    }
    this->players.erase(disconnected_id);
    plcount--;

    std::cout << "A player disconnected. Now online: " << plcount << " players." << std::endl;
    return std::make_shared<PlayerDisconnectedUpdate>(disconnected_id);
}

std::shared_ptr<Update> Game::process_new_connect(PlayerConnectedMessage& event) {
    std::lock_guard<std::mutex> lock(this->plmtx);
    plcount++;
    std::cout << "New player connected. Now online: " << plcount << " players." << std::endl;

    // makes new player the current player if lobby is empty
    if (this->curr_pl == this->players.end()) {
        this->curr_pl = this->players.find(event.get_id());

        this->eventq.push(std::make_shared<TurnAdvance>(SERVER_ID, this->curr_pl->first));
    }

    return std::make_shared<PlayerConnectedUpdate>(event.get_id());
}

std::shared_ptr<Update> Game::process_message(Chat& event) {
    return std::make_shared<ChatUpdate>(event.get_id(), event.get_msg());
}

std::shared_ptr<Update> Game::process_NullUpdate(NullMessage& event) {
    return std::make_shared<NullUpdate>();
}

std::shared_ptr<Update> Game::process_TurnAdvance(TurnAdvance& event) {
    std::lock_guard<std::mutex> lock(this->plmtx);

    int plid = event.get_new_pl_id();
    auto new_curr_pl = this->players.find(plid);

    if (new_curr_pl == this->players.end()) {
        std::cout << "Can't find id" << std::endl;
        return std::make_shared<NullUpdate>();
    }
    this->curr_pl = new_curr_pl;
    this->curr_pl->second->advance_worm();
    this->current_worm =
            std::make_pair(this->curr_pl->second->get_current_worm(), this->curr_pl->first);
    this->turn_start = std::chrono::steady_clock::now();
    std::cout << "New turn!" << std::endl;
    std::shared_ptr<BoxTurnAdvance> msg = std::make_shared<BoxTurnAdvance>(this->curr_pl->first);
    box2d.process(msg);
    return std::make_shared<TurnChange>(new_curr_pl->first);
}

std::shared_ptr<Update> Game::process_timer(RunTimer& event) {
    std::lock_guard<std::mutex> lock(this->plmtx);
    if (this->players.empty()) {
        return std::make_shared<NullUpdate>();
    }

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - this->turn_start);
    if (elapsed.count() >= this->turn_time) {
        ++this->curr_pl;
        if (this->curr_pl == this->players.end()) {
            this->curr_pl = this->players.begin();
        }
        if (this->curr_pl != this->players.end()) {
            this->eventq.push(std::make_shared<TurnAdvance>(SERVER_ID, this->curr_pl->first));
        }
    }
    return std::make_shared<TimerUpdate>(turn_time - elapsed.count(), this->current_worm.first);
}

std::shared_ptr<Update> Game::process_box2d(std::shared_ptr<Box2DMsg> event) {
    return std::shared_ptr<Update>(box2d.process(event));
}
