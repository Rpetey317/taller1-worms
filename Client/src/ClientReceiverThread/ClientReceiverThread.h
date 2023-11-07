#ifndef CLIENT_RECEIVER_THREAD_H
#define CLIENT_RECEIVER_THREAD_H

#include <mutex>
#include <string>

#include "../ClientProtocol/ClientProtocol.h"
#include "../Action/Action.h"

#include "queue.h"
#include "thread.h"

class ReceiverThread: public Thread {
    Queue<Action>& incomingq;
    ClientProtocol& prot;

public:
    ReceiverThread(Queue<Action>& incomingq, ClientProtocol& prot);
    void run() override;
    void end();

    ~ReceiverThread();
};


#endif  // CLIENT_RECEIVER_THREAD_H
