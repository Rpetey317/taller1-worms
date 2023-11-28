#ifndef CLIENT_SERVER_THREAD_H
#define CLIENT_SERVER_THREAD_H

#include <memory>
#include <mutex>
#include <string>

#include "../Action/Action.h"
#include "../ClientProtocol/ClientProtocol.h"

#include "queue.h"
#include "thread.h"

class SenderThread: public Thread {
    Queue<std::shared_ptr<Action>>& outgoingq;
    ClientProtocol& prot;

public:
    SenderThread(Queue<std::shared_ptr<Action>>& outgoingq, ClientProtocol& prot);
    void run() override;
    void end();

    ~SenderThread();
};


#endif  // CLIENT_SERVER_THREAD_H
