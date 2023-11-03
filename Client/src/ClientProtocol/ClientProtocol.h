#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <utility>
#include <variant>
#include <vector>

#include "Socket.h"
#include "string"
#include "NetworkProtocol.h"

using NetworkProtocol::msgcode_t;
using NetworkProtocol::msglen_t;
using NetworkProtocol::amount_players_t;
using NetworkProtocol::MSGCODE_PLAYER_MESSAGE;
// using NetworkProtocol::MSGCODE_PLAYER_CONNECT;
// using NetworkProtocol::MSGCODE_PLAYER_DISCONNECT;
using NetworkProtocol::ERROR;

class ClientProtocol {
private:
    Socket skt;
    std::string create_players_msg(int amount_players);
    bool was_closed;

public:
    explicit ClientProtocol(Socket skt);
    void client_send_msg(const std::string& chat_msg);
    msgcode_t recv_code();
    std::string recv_msg();
    int recv_amount_players();
    // uint8_t receive_gameupdate();
    void close();
    ~ClientProtocol();
};

#endif  // PROTOCOL_H
