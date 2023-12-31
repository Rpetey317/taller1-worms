#ifndef __SERVER_MESSENGER_H__
#define __SERVER_MESSENGER_H__

#include <memory>
#include <mutex>
#include <string>

#include "Message.h"
#include "ServerProtocol.h"
#include "queue.h"
#include "thread.h"

/*
 * Waits for new messages to be sent back to client
 */
class SenderThread: public Thread {
    Queue<std::shared_ptr<Update>>& sendq;
    ServerProtocol& prot;

public:
    /*
     * Initializes a new thread for a given client (prot)
     * Messages will be read from sendq
     */
    SenderThread(Queue<std::shared_ptr<Update>>& sendq, ServerProtocol& prot);

    /*
     * Runs the thread. Attempts to read message from queue. If a message is present,
     * sends it to player
     */
    void run() override;

    /*
     * sets the flag to stop running and closes incoming messages queue
     */
    void end();
};


#endif  // !__SERVER_MESSENGER_H__
