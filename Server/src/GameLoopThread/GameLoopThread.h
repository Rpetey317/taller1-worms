#ifndef GAME_LOOP_THREAD_H
#define GAME_LOOP_THREAD_H

#include <memory>

#include "Game.h"
#include "Message.h"
#include "queue.h"
#include "thread.h"

class GameLoopThread: public Thread {
    Queue<std::shared_ptr<Message>>& eventq;
    Game& game;

public:
    GameLoopThread(Queue<std::shared_ptr<Message>>& _eventq, Game& _game);

    void run() override;

    void stop() override;

    ~GameLoopThread() {}
};

#endif  // !GAME_LOOP_THREAD_H
