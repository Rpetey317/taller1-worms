#ifndef GAME_LOOP_THREAD_H
#define GAME_LOOP_THREAD_H

#include "Common/queue.h"
#include "Common/thread.h"
#include "Server/src/ClientUpdate/ClientUpdate.h"
#include "Server/src/Game/Game.h"

class GameLoopThread: public Thread {
    Queue<ClientUpdate>& eventq;
    GameHandler& game;

public:
    GameLoopThread(Queue<ClientUpdate>& _eventq, GameHandler& _game);

    void run() override;

    void stop() override;

    ~GameLoopThread() {}
};

#endif  // !GAME_LOOP_THREAD_H
