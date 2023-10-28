#ifndef __SERVER_RECEIVER_H__
#define __SERVER_RECEIVER_H__

#include "../common/queue.h"
#include "../common/thread.h"

#include "ClientUpdate.h"
#include "PlayerListMonitor.h"
#include "ServerProtocol.h"

/*
 * Constantly listens to client for new messages
 */
class ReceiverThread: public Thread {
    ReceiverListMonitor& recvers;
    ServerProtocol& prot;
    std::atomic<int>& plcount;


public:
    /*
     * Initializes a new thread for a given client (prot)
     * Incoming messages will be forvarded to recvers
     * When client disconnects, plcount is decremented
     */
    ReceiverThread(ReceiverListMonitor& recvers, ServerProtocol& prot, std::atomic<int>& plcount);

    /*
     * Runs thread. Listens for messages, and when one is received,
     * forwards it to all receivers. Stops when connection to client is closed
     */
    void run() override;

    /*
     * sets the flag to stop running
     */
    void end();
};

#endif  // __SERVER_RECEIVER_H__
