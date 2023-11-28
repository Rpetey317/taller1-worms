#ifndef __SERVER_PLMONITOR_H__
#define __SERVER_PLMONITOR_H__

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "ClientUpdateHeaders.h"
#include "GameUpdate.h"
#include "PlayerHandler.h"
#include "Socket.h"
#include "box2dManager.h"
#include "queue.h"

#define SERVER_ID 0

/*
 * Handles the game lobby and its players
 */
class Game {
    std::map<int, std::unique_ptr<PlayerHandler>> players;
    std::atomic<int> plcount;
    Queue<std::shared_ptr<ClientUpdate>>& eventq;
    std::map<int, std::unique_ptr<PlayerHandler>>::iterator curr_pl;
    int game_code;
    int next_free_id;
    Queue<int> box2d_in;
    Queue<std::vector<int>> box2d_out;
    BoxSimulator box2d;

public:
    // ============ DD ============= //
    // This three methods cannot be private. They are called from ClientUpdate::get_processed_by
    /*
     * Increments player count
     * Returns corresponding GamePlayerConnectedUpdate
     */
    std::shared_ptr<GameUpdate> process_new_connect(ClientConnectedUpdate& event);

    /*
     * Decrements player count
     * Returns corresponding GamePlayerDisconnectedUpdate
     */
    std::shared_ptr<GameUpdate> process_disconnect(ClientDisconnectedUpdate& event);

    /*
     * Returns GameChatMessageUpdate with same message
     */
    std::shared_ptr<GameUpdate> process_message(ClientMessageUpdate& event);

    /*
     * Processess NullUpdate (i.e. does nothing)
     */
    std::shared_ptr<GameUpdate> process_NullUpdate(ClientNullUpdate& event);

    /*
     * Advances turn to next player and notifies relevant players of the change
     */
    std::shared_ptr<GameUpdate> process_TurnAdvance(ClientPTurnAdvanceUpdate& event);

    std::shared_ptr<GameUpdate> process_box2d(ClientBox2DUpdate& event);


    /*
     * Creates new handler, adding players (recievers) to given list
     */
    explicit Game(Queue<std::shared_ptr<ClientUpdate>>& _eventq);
    // explicit GameHandler(Queue<std::shared_ptr<ClientUpdate>>& _eventq, int code);

    /*
     * Adds a new player, connected to given socket
     */
    void add_player(Socket&& player);

    /*
     * Executes given event, returns update to be sent back to players
     * Implemented via DD, a process_eventType method must be implemented for each event type
     */
    std::shared_ptr<GameUpdate> execute(std::shared_ptr<ClientUpdate> event);

    /*
     * broadcasts given update to all players
     */
    void broadcast(std::shared_ptr<GameUpdate> update);

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
