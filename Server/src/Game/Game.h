#ifndef __SERVER_PLMONITOR_H__
#define __SERVER_PLMONITOR_H__

#include <chrono>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "../Box2D/Box2dManager/box2dManager.h"

#include "MessageHeaders.h"
#include "PlayerHandler.h"
#include "ServerProtocol.h"
#include "Update.h"
#include "queue.h"

#define SERVER_ID 0

/*
 * Handles the game lobby and its players
 */
class Game {
    std::map<int, std::unique_ptr<PlayerHandler>> players;
    std::mutex plmtx;
    std::atomic<int> plcount;
    Queue<std::shared_ptr<Message>>& eventq;
    std::map<int, std::unique_ptr<PlayerHandler>>::iterator curr_pl;
    int game_code;
    int next_free_id;
    Queue<int> box2d_in;
    Queue<std::vector<int>> box2d_out;
    std::chrono::steady_clock::time_point turn_start;
    int turn_time;
    int worm_count;
    std::pair<int, int> current_worm;
    BoxManager box2d;

public:
    // ============ DD ============= //
    // This three methods cannot be private. They are called from Message::get_processed_by
    /*
     * Increments player count
     * Returns corresponding PlayerConnectedUpdate
     */
    std::shared_ptr<Update> process_new_connect(PlayerConnectedMessage& event);

    /*
     * Decrements player count
     * Returns corresponding PlayerDisconnectedUpdate
     */
    std::shared_ptr<Update> process_disconnect(PlayerDisconnectedMessage& event);

    /*
     * Returns ChatUpdate with same message
     */
    std::shared_ptr<Update> process_message(Chat& event);

    /*
     * Processess NullUpdate (i.e. does nothing)
     */
    std::shared_ptr<Update> process_NullUpdate(NullMessage& event);

    /*
     * Advances turn to next player and notifies relevant players of the change
     */
    std::shared_ptr<Update> process_TurnAdvance(TurnAdvance& event);

    std::shared_ptr<Update> process_box2d(std::shared_ptr<Box2DMsg> event);

    std::shared_ptr<Update> process_timer(RunTimer& event);

    /*
     * Creates new handler, adding players (recievers) to given list
     */
    explicit Game(Queue<std::shared_ptr<Message>>& _eventq);
    // explicit GameHandler(Queue<std::shared_ptr<Message>>& _eventq, int code);

    /*
     * Adds a new player, connected to given socket
     */
    void add_player(ServerProtocol&& player);

    /*
     * Executes given event, returns update to be sent back to players
     * Implemented via DD, a process_eventType method must be implemented for each event type
     */
    std::shared_ptr<Update> execute(std::shared_ptr<Message> event);

    /*
     * broadcasts given update to all players
     */
    void broadcast(std::shared_ptr<Update> update);

    void reset_timer();

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
