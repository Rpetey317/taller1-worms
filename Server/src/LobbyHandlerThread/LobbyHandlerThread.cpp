#include "LobbyHandlerThread.h"

LobbyHandlerThread::LobbyHandlerThread(Queue<std::unique_ptr<Socket>>& _queue) : queue(_queue) {}

void LobbyHandlerThread::run() {
    while (_keep_running) {
        std::unique_ptr<Socket> player = queue.pop();

        /* TODO:
         * - Receive a message from player
         * - If the message is a create game message, create a game
         * - If the message is a join game message, join the game
         * - If the game does not exist, send error to player and close connection
         */
    }
}
