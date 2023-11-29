#ifndef CLIENT_RECEIVER_THREAD_H
#define CLIENT_RECEIVER_THREAD_H

#include <memory>
#include <mutex>
#include <string>

#include "../ClientProtocol/ClientProtocol.h"
#include "../Event/Event.h"

#include "queue.h"
#include "thread.h"

class ReceiverThread: public Thread {
    Queue<std::shared_ptr<Event>>& incomingq;
    ClientProtocol& prot;

public:
    ReceiverThread(Queue<std::shared_ptr<Event>>& incomingq, ClientProtocol& prot);
    void run() override;
    void end();

    ~ReceiverThread();
};


#endif  // CLIENT_RECEIVER_THREAD_H
