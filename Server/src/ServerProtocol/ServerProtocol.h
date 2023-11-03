#ifndef __SERVER_PROTOCOL_H__
#define __SERVER_PROTOCOL_H__

#include <string>

#include "ClientUpdate.h"
#include "GameUpdateHeaders.h"
#include "Socket.h"

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
     * returns true if connection with client is still open
     */
    bool is_connected();

    char send_PlayerMessageUpdate(const PlayerMessageUpdate& upd);

    char send_TurnChangeUpdate(const TurnChangeUpdate& upd);
    
    char send_ConnectionAcknowledgeUpdate(const ConnectionAcknowledgeUpdate& upd);

    /*
     * Closes connection to client. Destructor already closes connection,
     * but this can be used to close from another thread
     */
    void close();
};

#endif  // !__SERVER_PROTOCOL_H__
