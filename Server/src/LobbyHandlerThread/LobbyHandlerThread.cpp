#include "LobbyHandlerThread.h"

#include <list>
#include <memory>
#include <string>
#include <utility>

#include "LibError.h"
#include "ServerProtocol.h"

LobbyHandlerThread::LobbyHandlerThread(Socket&& peer, LobbyHandler& _handler):
        player(std::move(peer)), handler(_handler) {}

void LobbyHandlerThread::send_game_data(GameDataRequest& request) {
    std::list<std::string> names = handler.get_game_names();
    player.send_game_data(names);
}

void LobbyHandlerThread::send_map_data(MapDataRequest& request) {
    std::list<std::string>& names = handler.get_map_names();
    player.send_map_data(names);
}

void LobbyHandlerThread::process_null_request(NullRequest& request) { _keep_running = false; }

void LobbyHandlerThread::run() {
    while (_keep_running) {

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
