#ifndef __ACCEPTERTHREAD_H__
#define __ACCEPTERTHREAD_H__

#include <list>
#include <memory>

#include "Game.h"
#include "LobbyHandler.h"
#include "LobbyHandlerThread.h"
#include "Message.h"
#include "Socket.h"
#include "queue.h"
#include "thread.h"

/*
 * Thread in charge of listening to connections and adding new players as they connect
 */
class ServerAccepterThread: public Thread {
    Socket acc;
    LobbyHandler& handler;
    std::list<std::unique_ptr<LobbyHandlerThread>> connecting_players;

    void reap_players();

public:
    /*
     * Creates new accepter thread, listening for connections in acc.
     * and adding any new players to lobby
     */
    ServerAccepterThread(Socket&& acc, LobbyHandler& lobby);
    // ServerAccepterThread(Socket&& acc);

    /*
     * Thread execution. Listens for new player connections, adds them to the handler,
     * and removes disconnected players until end() is called
     */
    void run() override;

    /*
     * Shuts down connection and ends thread execution
     */
    void end();

    ~ServerAccepterThread();
};

#endif  // __ACCEPTERTHREAD_H__
