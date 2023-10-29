#ifndef __SERVER_PROTOCOL_H__
#define __SERVER_PROTOCOL_H__

#include <string>

#include "common/Socket/Socket.h"

#define CLOSED_SKT -1
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
    void send_msg(const GameUpdate& msg);

    /*
     * Reads a message from client. Returns NO_MSG_READ if connection closed
     */
    ClientUpdate recv_msg();

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
