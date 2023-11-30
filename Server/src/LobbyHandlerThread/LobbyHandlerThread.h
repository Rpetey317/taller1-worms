#ifndef __LOBBYHANDLERTHREAD_H__
#define __LOBBYHANDLERTHREAD_H__

#include <memory>

#include "LobbyHandler.h"
#include "RequestHeaders.h"
#include "ServerProtocol.h"
#include "Socket.h"
#include "thread.h"

class LobbyHandlerThread: public Thread {
    LobbyHandler& handler;
    ServerProtocol player;

    friend class GameDataRequest;
    friend class MapDataRequest;
    friend class CreateRequest;
    friend class JoinRequest;
    friend class NullRequest;

    void send_game_data(GameDataRequest& request);
    void send_map_data(MapDataRequest& request);
    void join_game(JoinRequest& request);
    void create_game(CreateRequest& request);
    void process_null_request(NullRequest& request);

public:
    LobbyHandlerThread(Socket&& peer, LobbyHandler& handler);

    void run() override;

    void stop() override;

    ~LobbyHandlerThread();
};

#endif  // !__LOBBYHANDLERTHREAD_H__
