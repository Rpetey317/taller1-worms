#ifndef __SERVER_PLWRAPPER_H__
#define __SERVER_PLWRAPPER_H__

#include <list>
#include <memory>
#include <string>

#include "ReceiverThread.h"
#include "SenderThread.h"
#include "ServerProtocol.h"

/*
 * Handles all player resources in a RAII way
 */
class PlayerHandler {
    ServerProtocol prot;
    Queue<std::shared_ptr<Update>> sendq;
    SenderThread send_th;
    ReceiverThread recv_th;
    const int id;
    std::list<int> assigned_worms;
    std::list<int>::iterator last_worm_used;

public:
    /*
     * Creates new player connected to given socket. plcount and recvers should belong to a lobby
     * Creates (but doesn't start) 2 threads: one for receiving and one for sending
     * New player will be added to recvers, and a message notifying this will be sent
     * plcount is incremented, and when player disconnects, will be decremented
     */
    PlayerHandler(ServerProtocol&& peer, Queue<std::shared_ptr<Message>>& eventq, int& id);

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
    void send(std::shared_ptr<Update> msg);

    /*
     * Advances to next worm
     */
    void advance_worm();

    void assign_worm(int id);

    bool recv_start();

    std::list<int> get_worms();

    /*
     * Gets worm ID of next worm to use
     */
    int get_current_worm();

    /*
     * Stops associated threads and frees all resources
     */
    ~PlayerHandler();
};

#endif  // __SERVER_PLWRAPPER_H__
