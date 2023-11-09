#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <utility>
#include <variant>
#include <vector>

#include "../Action/ActionHeaders.h"
#include "../Action/Message/Message.h"
#include "../Event/EventHeaders.h"

#include "NetworkProtocol.h"
#include "Socket.h"
#include "string"

using namespace NetworkProtocol;

#define CLOSED_SKT -1
#define SUCCESS 0

class Message;  // Hardcodeo. Arreglar tema de includes

class ClientProtocol {
private:
    Socket skt;
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
    explicit ClientProtocol(Socket skt);
    int recv_player_id();

    /*
     * Send methods for each type of action.
     */
    char send_Message(Message action);

    // Sends code game
    void send_code_game(size_t code);

    Event* recv_update();

    msgcode_t recv_code();
    std::string recv_msg();
    int recv_amount_players();
    // uint8_t receive_gameupdate();
    void close();
    ~ClientProtocol();
};

#endif  // PROTOCOL_H
