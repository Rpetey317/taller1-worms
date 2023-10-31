#ifndef GAME_LOOP_THREAD_H
#define GAME_LOOP_THREAD_H

#include "ClientUpdate.h"
#include "Game.h"
#include "queue.h"
#include "thread.h"

class GameLoopThread: public Thread {
    Queue<ClientUpdate*>& eventq;
    GameHandler& game;

public:
    GameLoopThread(Queue<ClientUpdate*>& _eventq, GameHandler& _game);

    void run() override;

    void stop() override;

    ~GameLoopThread() {}
};

#endif  // !GAME_LOOP_THREAD_H
