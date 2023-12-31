#ifndef GAMEPROCESSING_H
#define GAMEPROCESSING_H

#include <atomic>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../ClientReceiverThread/ClientReceiverThread.h"
#include "../ClientSenderThread/ClientSenderThread.h"
#include "../EventProcessor/EventProcessor.h"

#include "Socket.h"
#include "queue.h"

class GameProcessing {
private:
    // Socket skt;
    ClientProtocol& protocol;
    Queue<std::shared_ptr<Action>>& outgoingq;  // For sender thread. SDL has a reference too
    Queue<std::shared_ptr<Event>>& incomingq;   // For receiver thread. SDL has a reference too
    ReceiverThread receiverTh;
    SenderThread senderTh;
    EventProcessor eventProcessor;
    int id;

public:
    /*
        Creates a GameProcessing object. It will create a socket and connect to the server.
        It will also create the threads for sending and receiving messages.
    */
    explicit GameProcessing(ClientProtocol& protocol, Queue<std::shared_ptr<Action>>& commands,
                            Queue<std::shared_ptr<Event>>& events);

    /*
        Checks if the command send by the user in the terminal is valid.
    */
    std::string ask_for_command();

    /*
        Runs the game. Receives the id of the client and runs the receiver and sender threads
    */
    void run();

    /*
        Returns the id of the client
    */
    int get_id();

    /*
        Ends the game. Joins the threads.
    */
    void end();

    ~GameProcessing();
};


#endif
