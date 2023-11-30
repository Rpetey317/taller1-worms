
#ifndef __LOBBYHANDLER_H__
#define __LOBBYHANDLER_H__

#include <map>
#include <memory>
#include <string>

#include "GameWrapper.h"

class LobbyHandler {
private:
    std::map<std::string, std::unique_ptr<GameWrapper>> games;

public:
    LobbyHandler();

    bool create_game(const std::string& name);

    bool join_player(const std::string& game, ServerProtocol&& player);

    ~LobbyHandler();
};


#endif  // __LOBBYHANDLER_H__
