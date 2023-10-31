#ifndef CLIENT_RECEIVER_THREAD_H
#define CLIENT_RECEIVER_THREAD_H

#include <mutex>
#include <string>

#include "queue.h"
#include "thread.h"

#include "ClientProtocol.h"

class ReceiverThread: public Thread {
    Queue<std::string>& incomingq; // Por ahora queue de strings
    ClientProtocol& prot;

public:
    ReceiverThread(Queue<std::string>& incomingq, ClientProtocol& prot);
    void run() override;
    void end();
};


#endif  // CLIENT_RECEIVER_THREAD_H