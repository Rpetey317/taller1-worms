#ifndef GAMEPROCESSING_H
#define GAMEPROCESSING_H

#include <atomic>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// #include "../ClientProtocol/ClientProtocol.h"
#include "../ClientReceiverThread/ClientReceiverThread.h"
#include "../ClientSenderThread/ClientSenderThread.h"

#include "Socket.h"
#include "queue.h"

class GameProcessing {
private:
    Socket skt;
    ClientProtocol protocol;  // El thread receiver y sender deberian tener el clientProtocol?
    Queue<Action> incomingq;
    Queue<Action> outgoingq;
    ReceiverThread receiverTh;
    SenderThread senderTh;

public:
    explicit GameProcessing(const char* hostname, const char* port);
    std::string ask_for_command();
    void run();
    ~GameProcessing();
};


#endif
