#include "LobbyHandler.h"

#include <list>
#include <memory>
#include <utility>

// All of this is yet untested

LobbyHandler::LobbyHandler(): games() {}

bool LobbyHandler::create_game(const std::string& game_name, const std::string& map_name) {
    /*
    if (games.find(game_name) != games.end()) {
        return false;
    }
    */
    std::cout << "Creating game " << game_name << " with map " << map_name << std::endl;
    games[game_name] = std::make_unique<GameWrapper>();
    return true;
}

void LobbyHandler::start_game(const std::string& game_name) {
    if (games.find(game_name) == games.end()) {
        return;
    }
    games[game_name]->start();
}

bool LobbyHandler::join_player(const std::string& game, ServerProtocol&& player) {
    if (games.find(game) == games.end()) {
        player.send_fail();
        return false;
    }
    std::cout << "Joining player to game " << game << std::endl;
    player.send_success();
    games[game]->add_player(std::move(player));
    return true;
}

std::list<std::string> LobbyHandler::get_game_names() {
    std::list<std::string> names;
    for (auto& game: games) {
        // cppcheck-suppress useStlAlgorithm
        names.push_back(game.first);
    }
    return names;
}

std::list<std::string> LobbyHandler::get_map_names() { return dummyList; }


LobbyHandler::~LobbyHandler() {
    for (auto& game: games) {
        game.second->~GameWrapper();
    }  // I trust copilot with my life (and my ram)
}
