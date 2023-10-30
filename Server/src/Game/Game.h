#ifndef __SERVER_PLMONITOR_H__
#define __SERVER_PLMONITOR_H__

#include <list>
#include <mutex>
#include <string>

#include "Common/Socket/Socket.h"
#include "Common/queue.h"
#include "Server/src/GameUpdate/GameUpdate.h"
#include "Server/src/PlayerHandler/PlayerHandler.h"
#include "Server/src/PlayerListMonitor/PlayerListMonitor.h"

/*
 * Handles the game lobby and its players
 */
class GameHandler {
    std::list<PlayerHandler*> players;
    std::atomic<int> plcount;
    Queue<ClientUpdate>& eventq;
    std::list<PlayerHandler*>::iterator curr_pl;

public:
    /*
     * Creates new handler, adding players (recievers) to given list
     */
    explicit GameHandler(Queue<ClientUpdate>& _eventq);

    /*
     * Adds a new player, connected to given socket
     */
    void add_player(Socket&& player);

    /*
     * Removes all disconected players from lobby, freeing related resources
     * This has no "gameplay" effects
     */
    void remove_disconnected();

    GameUpdate* execute(ClientUpdate event);

    void broadcast(GameUpdate* update);

    void advance_turn();

    /*
     * Closes lobby and frees all resources
     */
    void close();

    /*
     * Returns number of connected players
     */
    int count();
};

#endif  // !__SERVER_PLMONITOR_H__
