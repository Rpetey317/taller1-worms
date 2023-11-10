#ifndef __SERVER_PLMONITOR_H__
#define __SERVER_PLMONITOR_H__

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "ClientUpdateHeaders.h"
#include "GameUpdate.h"
#include "PlayerHandler.h"
#include "PlayerListMonitor.h"
#include "Socket.h"
#include "queue.h"

/*
 * Handles the game lobby and its players
 */
class GameHandler {
    std::map<int, std::unique_ptr<PlayerHandler>> players;
    std::atomic<int> plcount;
    Queue<ClientUpdate*>& eventq;
    std::map<int, std::unique_ptr<PlayerHandler>>::iterator curr_pl;
    int game_code;
    int next_free_id;


public:
    // ============ DD ============= //
    // This three methods cannot be private. They are called from ClientUpdate::get_processed_by
    /*
     * Increments player count
     * Returns corresponding GamePlayerConnectedUpdate
     */
    GameUpdate* process_new_connect(ClientConnectedUpdate& event);

    /*
     * Decrements player count
     * Returns corresponding GamePlayerDisconnectedUpdate
     */
    GameUpdate* process_disconnect(ClientDisconnectedUpdate& event);

    /*
     * Returns GameChatMessageUpdate with same message
     */
    GameUpdate* process_message(ClientMessageUpdate& event);

    GameUpdate* process_NullUpdate(ClientNullUpdate& event);

    GameUpdate* process_TurnAdvance(ClientPTurnAdvanceUpdate& event);


    /*
     * Creates new handler, adding players (recievers) to given list
     */
    explicit GameHandler(Queue<ClientUpdate*>& _eventq);
    // explicit GameHandler(Queue<ClientUpdate*>& _eventq, int code);

    /*
     * Adds a new player, connected to given socket
     */
    void add_player(Socket&& player);

    /*
     * Executes given event, returns update to be sent back to players
     * Implemented via DD, a process_eventType method must be implemented for each event type
     */
    GameUpdate* execute(ClientUpdate* event);


    void broadcast(GameUpdate* update);

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
