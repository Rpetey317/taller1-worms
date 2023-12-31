
#ifndef __LOBBYHANDLER_H__
#define __LOBBYHANDLER_H__

#include <list>
#include <map>
#include <memory>
#include <string>

#include "GameWrapper.h"

/*
 * Class that handles the server lobbies and the process
 * of assigning players to games
 */
class LobbyHandler {
private:
    std::map<std::string, std::unique_ptr<GameWrapper>> games;
    const std::list<std::string> maps;

public:
    LobbyHandler();

    bool create_game(const std::string& game_name, const std::string& map_name);

    void start_game(const std::string& game_name);

    bool join_player(const std::string& game, ServerProtocol&& player);
    bool join_host(const std::string& game, ServerProtocol&& player);

    std::list<std::string> get_game_names();
    std::list<std::string> get_map_names();

    ~LobbyHandler();
};


#endif  // __LOBBYHANDLER_H__
