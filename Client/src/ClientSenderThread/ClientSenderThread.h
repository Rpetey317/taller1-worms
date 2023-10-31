#ifndef CLIENT_SERVER_THREAD_H
#define CLIENT_SERVER_THREAD_H

#include <mutex>
#include <string>

#include "../ClientProtocol/ClientProtocol.h"

#include "queue.h"
#include "thread.h"

class SenderThread: public Thread {
    Queue<std::string>& outgoingq;  // Por ahora queue de strings
    ClientProtocol& prot;

public:
    SenderThread(Queue<std::string>& outgoingq, ClientProtocol& prot);
    void run() override;
    void end();

    ~SenderThread();
};


#endif  // CLIENT_SERVER_THREAD_H
