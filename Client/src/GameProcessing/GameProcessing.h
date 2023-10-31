#ifndef GAMEPROCESSING_H
#define GAMEPROCESSING_H

#include "ClientProtocol.h"
#include "Socket.h"
#include <utility>
#include <iostream>
#include <string>
#include <atomic>

class Client {
private:
    Socket skt;
    ClientProtocol protocol;
    std::atomic<bool> keep_talking;

public:
    explicit Client(const char *hostname, const char *port);
    void run();
    ~Client();
};


#endif
