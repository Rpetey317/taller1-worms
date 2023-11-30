#include "GameWrapper.h"

#include <utility>

GameWrapper::GameWrapper(): queue(), game(queue), game_loop(queue, game) { game_loop.start(); }

void GameWrapper::add_player(ServerProtocol&& player) { game.add_player(std::move(player)); }

GameWrapper::~GameWrapper() {
    game_loop.stop();
    game_loop.join();
}
