#ifndef __SERVER_PROTOCOL_H__
#define __SERVER_PROTOCOL_H__

#include <string>

#include "ClientUpdate.h"
#include "GameUpdateHeaders.h"
#include "Socket.h"

#include "NetworkProtocol.h"

using NetworkProtocol::msgcode_t;
using NetworkProtocol::msglen_t;

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

public:
    /*
     * Constructs a new protocol from socket with move semantics
     */
    explicit ServerProtocol(Socket&& cli);

    /*
     * Sends given message to client
     */
    char send_update(GameUpdate* msg);

    /*
     * Reads a message from client. Returns NO_MSG_READ if connection closed
     */
    ClientUpdate recv_msg();

    /*
    * Reads the first request the client sends. Can be CREATE_GAME or JOIN_GAME
    */
    msgcode_t recv_request();

    /*
    * Reads the code of the game the client wants to join
    */
    size_t recv_join();

    /*
     * returns true if connection with client is still open
     */
    bool is_connected();

    char send_PlayerMessageUpdate(const PlayerMessageUpdate& upd);

    /*
     * Closes connection to client. Destructor already closes connection,
     * but this can be used to close from another thread
     */
    void close();
};

#endif  // !__SERVER_PROTOCOL_H__
