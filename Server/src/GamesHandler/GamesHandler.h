
#ifndef GAMESHANDLER_H
#define GAMESHANDLER_H
#include <string>
#include <vector>

#include "Game.h"

class GamesHandler {
private:
    size_t code;
    std::vector<GameHandler*> games;
    std::mutex m;
  
    // ServerProtocol prot;

  public:
    GamesHandler();
    GameHandler* create_GamesHandler();
    // GameHandler* join_GamesHandler(size_t code);
    void add_player(Socket&& player);
    void remove_disconnected();
    ~GamesHandler();
};


#endif  // GAMESHANDLER_H
