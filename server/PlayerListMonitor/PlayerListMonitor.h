#ifndef __SERVER_LISTMONITOR_H__
#define __SERVER_LISTMONITOR_H__

#include <list>
#include <mutex>

#include "common/queue.h"
#include "server/ClientUpdate/ClientUpdate.h"

/*
 * Thread-safe list of queues of messages.
 * No memory is allocated nor freed by this class
 */
class ReceiverListMonitor {
private:
    std::list<Queue<ClientUpdate>*> recvers;
    std::mutex mtx;

public:
    /*
     * Default constructor for empty list
     */
    ReceiverListMonitor();

    /*
     * Adds recver queue to the list
     */
    void add_recver(Queue<ClientUpdate>* recver);

    /*
     * Pushes a message to all reciever queues
     * Also prints message to std::out and removes closed queues
     */
    void push_to_all(ClientUpdate msg);

    /*
     * Default destructor for list. Does not call delete for an pointer
     */
    ~ReceiverListMonitor();
};


#endif  // !__SERVER_LISTMONITOR_H__
