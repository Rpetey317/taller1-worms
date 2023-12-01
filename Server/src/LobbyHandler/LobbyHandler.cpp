#include "LobbyHandler.h"

#include <list>
#include <memory>
#include <utility>

// All of this is yet untested

LobbyHandler::LobbyHandler(): games() {}

bool LobbyHandler::create_game(const std::string& game_name, const std::string& map_name) {
    if (games.find(game_name) != games.end()) {
        return false;
    }
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
        return false;
    }
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

LobbyHandler::~LobbyHandler() {
    for (auto& game: games) {
        game.second->~GameWrapper();
    }  // I trust copilot with my life (and my ram)
}
