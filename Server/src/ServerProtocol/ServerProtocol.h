#ifndef __SERVER_PROTOCOL_H__
#define __SERVER_PROTOCOL_H__

#include <string>

#include "ClientUpdateHeaders.h"
#include "GameUpdateHeaders.h"
#include "NetworkProtocol.h"
#include "Socket.h"

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
    const int plid;

    /*
     * Primitive type send methods, to simplify update-specific send methods
     * On successful send returns true, false if socket closed
     */
    bool send_short(const uint16_t& num);
    bool send_long(const uint32_t& num);
    bool send_char(const uint8_t& num);
    bool send_str(const std::string& str);


public:
    // ========== DD ============ //
    // This methods need to be public, because they are called from GameHandler::process_new_connect
    /*
     * Send methods for each type of update.
     * Refer to protocol documentation for details
     */
    char send_ConnectionAcknowledgeUpdate(const GameAcknowledgeUpdate& upd);
    char send_PlayerConnectedUpdate(const GamePlayerConnectedUpdate& upd);
    char send_PlayerDisconnectedUpdate(const GamePlayerDisconnectedUpdate& upd);
    char send_TurnChangeUpdate(const GameTurnChangeUpdate& upd);
    char send_PlayerMessageUpdate(const GameChatMessageUpdate& upd);
    char send_NullUpdate(const GameNullUpdate& upd);
    char send_WorldUpdate(const GameWorldUpdate& upd);


    /*
     * Constructs a new protocol from socket with move semantics
     */
    ServerProtocol(Socket&& cli, const int& plid);

    /*
     * Sends given message to client
     */
    char send_update(GameUpdate* msg);

    /*
     * Reads a message from client. Returns NullMsg if connection closed
     */
    ClientUpdate* recv_update();

    /*
     * Reads the first request the client sends. Can be CREATE_GAME or JOIN_GAME
     */
    msgcode_t recv_request();

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
