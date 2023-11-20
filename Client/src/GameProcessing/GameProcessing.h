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
#include "../EventProcessor/EventProcessor.h"

#include "Socket.h"
#include "queue.h"

class GameProcessing {
private:
    Socket skt;
    ClientProtocol protocol;  // El thread receiver y sender deberian tener el clientProtocol?
    Queue<Event*> incomingq;
    Queue<Action*> outgoingq;
    Queue<Action*>& actions;
    ReceiverThread receiverTh;
    SenderThread senderTh;
    EventProcessor eventProcessor;
    int id;

public:
    explicit GameProcessing(const char* hostname, const char* port);

    explicit GameProcessing(const char* hostname, const char* port, Queue<Action*>& commands);

    std::string ask_for_command();
    void run();
    void alternate_run();
    int get_id();
    ~GameProcessing();
};


#endif
