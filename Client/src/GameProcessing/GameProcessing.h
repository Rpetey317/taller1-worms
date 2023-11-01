#ifndef GAMEPROCESSING_H
#define GAMEPROCESSING_H

#include <atomic>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <map>

#include "../ClientProtocol/ClientProtocol.h"

#include "Socket.h"

class GameProcessing {
private:
    Socket skt;
    ClientProtocol protocol;  // El thread receiver y sender deberian tener el clientProtocol?

public:
    explicit GameProcessing(const char* hostname, const char* port);
    std::string ask_for_command();
    void run();
    ~GameProcessing();
};


#endif
