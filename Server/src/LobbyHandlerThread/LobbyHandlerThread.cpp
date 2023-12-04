#include "LobbyHandlerThread.h"

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <utility>

#include "LibError.h"
#include "ServerProtocol.h"

LobbyHandlerThread::LobbyHandlerThread(Socket&& peer, LobbyHandler& _handler):
        handler(_handler), player(std::move(peer)) {}

void LobbyHandlerThread::send_game_data(GameDataRequest& request) {
    std::list<std::string> names = handler.get_game_names();
    player.send_game_data(names);
}

void LobbyHandlerThread::send_map_data(MapDataRequest& request) {
    std::list<std::string> names = handler.get_map_names();
    player.send_map_data(names);
}

void LobbyHandlerThread::join_game(JoinRequest& request) {
    std::string& game_name = request.get_name();
    std::cout << "Joining player to game " << game_name << std::endl;

    if (!handler.join_player(game_name, std::move(player))) {
        _keep_running = false;
    }
}

void LobbyHandlerThread::create_game(CreateRequest& request) {
    std::string& game_name = request.get_game_name();
    std::string& map_name = request.get_map_name();
    std::cout << "Creating game " << game_name << " with map " << map_name << std::endl;

    // TODO: check if map_name is valid

    handler.create_game(game_name, map_name);
    if (!handler.join_host(game_name, std::move(player))) {
        return;
    }

    _keep_running = false;
}

void LobbyHandlerThread::process_null_request(NullRequest& request) { _keep_running = false; }

void LobbyHandlerThread::run() {
    std::cout << "Lobby handler thread started\n";
    while (_keep_running) {
        std::cout << "Tuki" << std::endl;
        try {
            auto request = player.recv_request();
            request->get_processed_by(*this);
        } catch (LibError& e) {  // Socket closed
            _keep_running = false;
        } catch (...) {
            std::cerr << "Unknown error when joining player to lobby\n";
            _keep_running = false;
        }
    }
}

bool LobbyHandlerThread::is_dead() { return !_keep_running; }

void LobbyHandlerThread::stop() {
    if (_keep_running)
        player.close();
    _keep_running = false;
}

LobbyHandlerThread::~LobbyHandlerThread() {}
