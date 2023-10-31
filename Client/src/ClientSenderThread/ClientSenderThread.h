#ifndef CLIENT_SERVER_THREAD_H
#define CLIENT_SERVER_THREAD_H

#include <mutex>
#include <string>

#include "queue.h"
#include "thread.h"

#include "ClientProtocol.h"

class SenderThread: public Thread {
    Queue<std::string>& outgoingq; // Por ahora queue de strings
    ClientProtocol& prot;

public:
    SenderThread(Queue<std::string>& outgoingq, ClientProtocol& prot);
    void run() override;
    void end();
};


#endif  // CLIENT_SERVER_THREAD_H