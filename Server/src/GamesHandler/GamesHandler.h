
#ifndef GAMESHANDLER_H
#define GAMESHANDLER_H
#include "Game.h"
#include <vector>
#include <string>

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


#endif //GAMESHANDLER_H