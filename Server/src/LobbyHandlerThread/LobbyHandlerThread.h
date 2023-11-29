#ifndef __LOBBYHANDLERTHREAD_H__
#define __LOBBYHANDLERTHREAD_H__

#include "thread.h"
#include "queue.h"
#include "Socket.h"
#include "LobbyHandler.h"

class LobbyHandlerThread : public Thread {
    LobbyHandler handler;
    Queue<std::unique_ptr<Socket>>& queue;

public:
    LobbyHandlerThread(Queue<std::unique_ptr<Socket>>& queue);

    void run() override;

    void stop() override;

    ~LobbyHandlerThread();
};

#endif // !__LOBBYHANDLERTHREAD_H__
