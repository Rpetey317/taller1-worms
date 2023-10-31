#ifndef GAMEPROCESSING_H
#define GAMEPROCESSING_H

#include "ClientProtocol.h"
#include "Socket.h"
#include <utility>
#include <iostream>
#include <string>
#include <atomic>

class GameProcessing {
private:
    Socket skt;
    ClientProtocol protocol; // El thread receiver y sender deberian tener el clientProtocol?
    std::atomic<bool> keep_talking;

public:
    explicit GameProcessing(const char *hostname, const char *port);
    void run();
    ~GameProcessing();
};


#endif
