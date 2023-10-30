#ifndef __SERVER_RECEIVER_H__
#define __SERVER_RECEIVER_H__

#include "Common/queue.h"
#include "Common/thread.h"
#include "Server/src/ClientUpdate/ClientUpdate.h"
#include "Server/src/PlayerListMonitor/PlayerListMonitor.h"
#include "Server/src/ServerProtocol/ServerProtocol.h"

/*
 * Constantly listens to client for new messages
 */
class ReceiverThread: public Thread {
    Queue<ClientUpdate>& eventq;
    ServerProtocol& prot;
    std::atomic<int>& plcount;


public:
    /*
     * Initializes a new thread for a given client (prot)
     * Incoming messages will be forvarded to recvers
     * When client disconnects, plcount is decremented
     */
    ReceiverThread(Queue<ClientUpdate>& eventq, ServerProtocol& prot, std::atomic<int>& plcount);

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
