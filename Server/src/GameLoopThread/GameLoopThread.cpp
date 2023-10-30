#include "Server/src/GameLoopThread/GameLoopThread.h"

#include <chrono>

const std::chrono::milliseconds tickrate(16);

GameLoopThread::GameLoopThread(Queue<ClientUpdate>& _eventq, GameHandler& _game):
        eventq(_eventq), game(_game) {}

void GameLoopThread::run() {
    while (_keep_running) {
        ClientUpdate event;
        auto start_time = std::chrono::steady_clock::now();

        // Try to pop something from the event queue
        bool popped = this->eventq.try_pop(event);

        // Execute said action if needed
        if (popped) {
            GameUpdate* update = this->game.execute(event);
            game.broadcast(update);
            delete update;
        }

        // Take time elapsed
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_time =
                std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        auto time_to_sleep = std::chrono::milliseconds(tickrate - elapsed_time);

        // Sleep for the remaining time
        if (time_to_sleep.count() > 0) {
            // Sleep until t milliseconds have passed
            std::chrono::steady_clock::time_point end =
                    std::chrono::steady_clock::now() + time_to_sleep;
            std::this_thread::sleep_until(end);
        }

        // Advance turn and loop
        game.advance_turn();
    }
}

void GameLoopThread::stop() { _keep_running = false; }
