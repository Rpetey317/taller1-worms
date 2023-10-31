#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

#include "../ClientParser/ClientParser.h"
#include "../ClientProtocol/ClientProtocol.h"
#include "Socket.h"

class Client {
private:
    ClientParser parser;
    ClientProtocol protocol;

public:
    Client(const char* hostname, const char* port);
    std::string ask_for_command();
    void play();
    ~Client();
};

#endif  // CLIENT_H
