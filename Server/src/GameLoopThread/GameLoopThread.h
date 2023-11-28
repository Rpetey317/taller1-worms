#ifndef GAME_LOOP_THREAD_H
#define GAME_LOOP_THREAD_H

#include <memory>

#include "ClientUpdate.h"
#include "Game.h"
#include "queue.h"
#include "thread.h"

class GameLoopThread: public Thread {
    Queue<std::shared_ptr<ClientUpdate>>& eventq;
    GameHandler& game;

public:
    GameLoopThread(Queue<std::shared_ptr<ClientUpdate>>& _eventq, GameHandler& _game);

    void run() override;

    void stop() override;

    ~GameLoopThread() {}
};

#endif  // !GAME_LOOP_THREAD_H
