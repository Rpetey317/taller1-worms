#include "LobbyHandlerThread.h"

#include <memory>
#include <utility>

#include "LibError.h"
#include "ServerProtocol.h"

LobbyHandlerThread::LobbyHandlerThread(Queue<std::shared_ptr<Socket>>& _queue): queue(_queue) {}

void LobbyHandlerThread::run() {
    while (_keep_running) {
        std::shared_ptr<Socket> peer = queue.pop();

        ServerProtocol player(std::move(*peer));

        try {

        } catch (LibError& e) {
            // TODO: handle socket closed error;
        } catch (...) {
            std::cerr << "Unknown error when joining player to lobby\n";
        }


        /* TODO:
         * - Receive a message from player
         * - If the message is a create game message, create a game
         * - If the message is a join game message, join the game
         * - If the game does not exist, send error to player and close connection
         */
    }
}
