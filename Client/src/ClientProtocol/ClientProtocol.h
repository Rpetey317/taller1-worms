#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <utility>
#include <variant>
#include <vector>

#include "../ClientParser/ClientParser.h"

#include "Socket.h"
#include "string"

class ClientProtocol {
private:
    Socket skt;
    std::string create_players_msg(int amount_players);

public:
    explicit ClientProtocol(Socket skt);
    void client_send_msg(std::vector<std::variant<uint8_t, uint16_t>> parsed_command);
    std::string recv_msg();
    uint8_t receive_gameupdate();
    ~ClientProtocol();
};

#endif  // PROTOCOL_H
