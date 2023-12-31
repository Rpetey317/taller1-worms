#ifndef __SERVER_PROTOCOL_H__
#define __SERVER_PROTOCOL_H__

#include <list>
#include <memory>
#include <string>

#include "MessageHeaders.h"
#include "NetworkProtocol.h"
#include "RequestHeaders.h"
#include "Socket.h"
#include "UpdateHeaders.h"
#include "Vect2D.h"

using NetworkProtocol::msgcode_t;
using NetworkProtocol::strlen_t;

using NetworkProtocol::MSGCODE_PLAYER_DISCONNECT;
using NetworkProtocol::MSGCODE_PLAYER_MESSAGE;

#define CLOSED_SKT -1
#define SUCCESS 0
#define NO_MSG_RECV ""


/*
 * Wrapper for a socket communicating with client
 * Serializes and sends messages, and de-serializes incoming ones
 */
class ServerProtocol {
    Socket cli;
    bool isclosed;

    /*
     * Primitive type send methods, to simplify update-specific send methods
     * On successful send returns true, false if socket closed
     */
    bool send_short(const uint16_t& num);
    bool send_long(const uint32_t& num);
    bool send_char(const uint8_t& num);
    bool send_str(const std::string& str);
    bool send_Vect2D(const Vect2D& pt);
    bool send_Worm(const Worm& pt);
    bool send_weapon(const WeaponDTO& wpn);

    /*
     * Primitive type receive methods, to simplify update-specific receive methods
     * On successful receive return true, false if socket closed
     */
    bool recv_char(uint8_t& num);
    bool recv_short(uint16_t& num);
    bool recv_long(uint32_t& num);
    bool recv_str(std::string& str);

public:
    // ========== DD ============ //
    // This methods need to be public, because they are called from Game::process_new_connect
    /*
     * Send methods for each type of update.
     * Refer to protocol documentation for details
     */
    char send_ConnectionAcknowledgeUpdate(const PlayerAcknowledge& upd);
    char send_PlayerConnectedUpdate(const PlayerConnectedUpdate& upd);
    char send_PlayerDisconnectedUpdate(const PlayerDisconnectedUpdate& upd);
    char send_TurnChangeUpdate(const TurnChange& upd);
    char send_PlayerMessageUpdate(const ChatUpdate& upd);
    char send_NullUpdate(const NullUpdate& upd);
    char send_WorldUpdate(const WorldUpdate& upd);
    char send_TimerUpdate(const TimerUpdate& upd);
    char send_Start(const StartUpdate& upd);


    char send_game_data(const std::list<std::string>& names);
    char send_map_data(const std::list<std::string>& names);
    char send_success();
    char send_fail();

    /*
     * Constructs a new protocol from socket with move semantics
     */
    explicit ServerProtocol(Socket&& cli);

    ServerProtocol(const ServerProtocol&) = delete;

    ServerProtocol(ServerProtocol&& other);

    /*
     * Sends given message to client
     */
    char send_update(std::shared_ptr<Update> msg);

    /*
     * Reads a message from client. Returns NullMsg if connection closed
     */
    std::shared_ptr<Message> recv_update(const int& plid);

    std::unique_ptr<Request> recv_request();

    bool recv_game_start();

    /*
     * Reads the code of the game the client wants to join
     */
    size_t recv_join();

    /*
     * returns true if connection with client is still open
     */
    bool is_connected();

    /*
     * Closes connection to client. Destructor already closes connection,
     * but this can be used to close from another thread
     */
    void close();
};

#endif  // !__SERVER_PROTOCOL_H__
