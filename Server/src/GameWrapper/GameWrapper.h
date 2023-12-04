#ifndef __GAMEWRAPPER_H__
#define __GAMEWRAPPER_H__

#include <memory>
#include <string>

#include "Game.h"
#include "GameLoopThread.h"
#include "ServerProtocol.h"
#include "queue.h"

class GameWrapper {
    Queue<std::shared_ptr<Message>> queue;
    Game game;
    GameLoopThread game_loop;

public:
    explicit GameWrapper(const std::string& map_name);

    void add_player(ServerProtocol&& player);
    void add_host(ServerProtocol&& player);

    void start();

    ~GameWrapper();
};

#endif  // !__GAMEWRAPPER_H__
