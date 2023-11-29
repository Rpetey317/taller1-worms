
#ifndef __LOBBYHANDLER_H__
#define __LOBBYHANDLER_H__

#include <string>
#include <map>

#include "GameWrapper.h"

class LobbyHandler {
private:
    std::map<std::string, std::unique_ptr<GameWrapper>> games;
  
public:
    LobbyHandler();

    bool create_game(const std::string& name);

    bool join_player(const std::string& game, Socket&& player);

    ~LobbyHandler();
};


#endif  // __LOBBYHANDLER_H__
