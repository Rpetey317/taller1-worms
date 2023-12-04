#include "GameWrapper.h"

#include <utility>

GameWrapper::GameWrapper(const std::string& _name):
        queue(), game(queue, _name), game_loop(queue, game) {}

void GameWrapper::add_player(ServerProtocol&& player) { game.add_player(std::move(player)); }
void GameWrapper::add_host(ServerProtocol&& player) { game.add_host(std::move(player)); }

void GameWrapper::start() { game_loop.start(); }

GameWrapper::~GameWrapper() {
    game_loop.stop();
    game_loop.join();
}
