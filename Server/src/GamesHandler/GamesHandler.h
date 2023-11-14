
#ifndef GAMESHANDLER_H
#define GAMESHANDLER_H
#include <string>
#include <vector>

#include "Game.h"

class GamesHandler {
private:
    int code;
    std::vector<GameHandler*> games;
    std::mutex m;

public:
    GamesHandler();
    GameHandler* create_GamesHandler(Queue<ClientUpdate*>& client_queue);
    GameHandler* join_GamesHandler(int code, Queue<ClientUpdate*>& client_queue);
    ~GamesHandler();
};


#endif  // GAMESHANDLER_H
