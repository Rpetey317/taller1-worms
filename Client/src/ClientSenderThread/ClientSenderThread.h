#ifndef CLIENT_SERVER_THREAD_H
#define CLIENT_SERVER_THREAD_H

#include <mutex>
#include <string>

#include "../Action/Action.h"
#include "../ClientProtocol/ClientProtocol.h"

#include "queue.h"
#include "thread.h"

class SenderThread: public Thread {
    Queue<Action*>& outgoingq;
    ClientProtocol& prot;

public:
    SenderThread(Queue<Action*>& outgoingq, ClientProtocol& prot);
    void run() override;
    void end();

    ~SenderThread();
};


#endif  // CLIENT_SERVER_THREAD_H
