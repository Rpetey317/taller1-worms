#include "GameLoopThread.h"

#include <chrono>
#include <list>
#include <memory>

const std::chrono::milliseconds tickrate(1000 / 60);

GameLoopThread::GameLoopThread(Queue<std::shared_ptr<ClientUpdate>>& _eventq, GameHandler& _game):
        eventq(_eventq), game(_game) {}

void GameLoopThread::run() {
    while (_keep_running) {
        std::list<std::shared_ptr<ClientUpdate>> event_list;
        auto start_time = std::chrono::steady_clock::now();

        // Pop everything from event queue
        bool popped = false;
        do {
            std::shared_ptr<ClientUpdate> event;
            popped = this->eventq.try_pop(event);
            if (popped) {
                event_list.push_back(event);
            }
        } while (popped);

        // Execute actions if needed
        for (auto event: event_list) {
            std::shared_ptr<GameUpdate> update = this->game.execute(event);
            game.broadcast(update);
            // delete update;
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

        // std::cout << "Tick" << std::endl;
    }
}

void GameLoopThread::stop() { _keep_running = false; }
