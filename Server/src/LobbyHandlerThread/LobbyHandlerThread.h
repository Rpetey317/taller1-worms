#ifndef __LOBBYHANDLERTHREAD_H__
#define __LOBBYHANDLERTHREAD_H__

#include <memory>

#include "LobbyHandler.h"
#include "RequestHeaders.h"
#include "ServerProtocol.h"
#include "Socket.h"
#include "thread.h"

class LobbyHandlerThread: public Thread {
    LobbyHandler handler;
    ServerProtocol player;

    void send_game_data(GameDataRequest& request);
    void send_map_data(MapDataRequest& request);
    void join_game();
    void create_game();

public:
    explicit LobbyHandlerThread(Socket&& peer);

    void run() override;

    void stop() override;

    ~LobbyHandlerThread();
};

#endif  // !__LOBBYHANDLERTHREAD_H__
