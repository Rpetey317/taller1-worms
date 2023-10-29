#ifndef __SERVER_PLWRAPPER_H__
#define __SERVER_PLWRAPPER_H__

#include <list>

#include "server/PlayerListMonitor/PlayerListMonitor.h"
#include "server/ReceiverThread/ReceiverThread.h"
#include "server/SenderThread/SenderThread.h"

/*
 * Handles all player resources in a RAII way
 */
class PlayerHandler {
    ServerProtocol prot;
    Queue<ClientUpdate> sendq;
    ReceiverListMonitor& recvers;
    SenderThread send_th;
    ReceiverThread recv_th;

public:
    /*
     * Creates new player connected to given socket. plcount and recvers should belong to a lobby
     * Creates (but doesn't start) 2 threads: one for receiving and one for sending
     * New player will be added to recvers, and a message notifying this will be sent
     * plcount is incremented, and when player disconnects, will be decremented
     */
    PlayerHandler(Socket&& peer, std::atomic<int>& plcount, ReceiverListMonitor& recvers);

    /*
     * Starts to run associated threads
     */
    void start();

    /*
     * Returns true if player is still connected
     */
    bool is_connected();

    /*
     * Sends a message back to client
     */
    void send(const ClientUpdate& msg);

    /*
     * Stops associated threads and frees all resources
     */
    ~PlayerHandler();
};

#endif  // __SERVER_PLWRAPPER_H__
