
#ifndef GAMESHANDLER_H
#define GAMESHANDLER_H
#include <string>
#include <vector>

#include "Game.h"

class GamesHandler {
private:
    int code;
    std::vector<Game*> games;
    std::mutex m;
  
    // ServerProtocol prot;

  public:
    GamesHandler();
    Game* create_GamesHandler(Queue<Message*>& client_queue);
    Game* join_GamesHandler(int code, Queue<Message*>& client_queue);
    ~GamesHandler();
};


#endif  // GAMESHANDLER_H
