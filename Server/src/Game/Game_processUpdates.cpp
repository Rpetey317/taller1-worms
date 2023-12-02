#include <iterator>
#include <memory>
#include <chrono>

#include "Game.h"

std::shared_ptr<Update> Game::process_disconnect(PlayerDisconnectedMessage& event) {
    int disconnected_id = event.get_id();
    if (this->curr_pl->first == disconnected_id) {
        auto nx_pl = std::next(this->curr_pl);
        if (nx_pl == this->players.end()) {
            nx_pl = this->players.begin();
        }
        // since player is no longer in the game, "server" sends this update
        this->eventq.push(std::make_shared<TurnAdvance>(SERVER_ID, nx_pl));
    }
    this->players.erase(disconnected_id);
    plcount--;

    std::cout << "A player disconnected. Now online: " << plcount << " players." << std::endl;
    return std::make_shared<PlayerDisconnectedUpdate>(disconnected_id);
}

std::shared_ptr<Update> Game::process_new_connect(PlayerConnectedMessage& event) {
    plcount++;
    std::cout << "New player connected. Now online: " << plcount << " players." << std::endl;

    // makes new player the current player if lobby is empty
    if (this->curr_pl == this->players.end()) {
        this->curr_pl = this->players.find(event.get_id());

        // event is generated by "server" since lobby is empty
        this->eventq.push(std::make_shared<TurnAdvance>(SERVER_ID, this->curr_pl));
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
    auto new_curr_pl = event.get_new_pl();

    if (new_curr_pl == this->players.end()) {
        return std::make_shared<NullUpdate>();
    }
    this->curr_pl = new_curr_pl;
    this->turn_start = std::chrono::steady_clock::now();
    std::cout << "New turn!" << std::endl;
    return std::make_shared<TurnChange>(new_curr_pl->first);
}

std::shared_ptr<Update> Game::process_timer(RunTimer& event) {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - this->turn_start);
    std::cout << "Time left: " << turn_time - elapsed.count() << std::endl;
    if (elapsed.count() >= this->turn_time) {
        std::cout << "Time's up!" << std::endl;
        auto new_curr_pl = this->curr_pl == this->players.end() ? this->players.begin() : std::next(this->curr_pl);
        if (new_curr_pl != this->players.end()) {
            this->eventq.push(std::make_shared<TurnAdvance>(SERVER_ID, new_curr_pl));
            std::cout << "Update pushed!" << std::endl;
            return std::make_shared<TimerUpdate>(turn_time - elapsed.count(), new_curr_pl->first);
        }
    }

    return std::make_shared<TimerUpdate>(turn_time - elapsed.count(), this->curr_pl->first);
}

std::shared_ptr<Update> Game::process_box2d(Box2DMsg& event) {
    return std::shared_ptr<Update>(box2d.process(event));
}
