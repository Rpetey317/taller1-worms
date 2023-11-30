#include "LobbyHandler.h"

#include <list>
#include <memory>
#include <utility>

// All of this is yet untested

LobbyHandler::LobbyHandler(): games() {}

bool LobbyHandler::create_game(const std::string& name) {
    if (games.find(name) != games.end()) {
        return false;
    }
    games[name] = std::make_unique<GameWrapper>();
    return true;
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
        names.push_back(game.first);
    }
    return names;
}

LobbyHandler::~LobbyHandler() {
    for (auto& game: games) {
        game.second->~GameWrapper();
    }  // I trust copilot with my life (and my ram)
}
