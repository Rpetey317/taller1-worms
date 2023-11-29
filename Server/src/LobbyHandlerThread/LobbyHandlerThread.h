#ifndef __LOBBYHANDLERTHREAD_H__
#define __LOBBYHANDLERTHREAD_H__

#include <memory>

#include "LobbyHandler.h"
#include "Socket.h"
#include "queue.h"
#include "thread.h"

class LobbyHandlerThread: public Thread {
    LobbyHandler handler;
    Queue<std::shared_ptr<Socket>>& queue;

public:
    explicit LobbyHandlerThread(Queue<std::shared_ptr<Socket>>& queue);

    void run() override;

    void stop() override;

    ~LobbyHandlerThread();
};

#endif  // !__LOBBYHANDLERTHREAD_H__
