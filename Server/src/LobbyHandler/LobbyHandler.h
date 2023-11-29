
#ifndef __LOBBYHANDLER_H__
#define __LOBBYHANDLER_H__

#include <string>
#include <map>

#include "Game.h"

class LobbyHandler {
private:
    int code;
    std::map<std::string, std::unique_ptr<Game>> games;
    std::mutex m;
  
    // ServerProtocol prot;

  public:
    LobbyHandler();
    Game* create_LobbyHandler(Queue<Message*>& client_queue);
    Game* join_LobbyHandler(int code, Queue<Message*>& client_queue);
    ~LobbyHandler();
};


#endif  // __LOBBYHANDLER_H__
