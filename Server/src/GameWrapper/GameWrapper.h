#ifndef __GAMEWRAPPER_H__
#define __GAMEWRAPPER_H__

#include <memory>

#include "Game.h"
#include "GameLoopThread.h"
#include "Socket.h"
#include "queue.h"

class GameWrapper {
    Queue<std::shared_ptr<Message>> queue;
    Game game;
    GameLoopThread game_loop;

public:
    GameWrapper();

    void add_player(Socket&& player);

    ~GameWrapper();
};

#endif  // !__GAMEWRAPPER_H__
